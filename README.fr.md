# Minishell

> Un shell POSIX écrit en C pur (~4000 lignes), sans utiliser la moindre lib de parsing : lexer, pipeline, redirections et gestion des signaux réimplémentés à la main.

## 🎯 Pourquoi ce projet ? (Contexte & Problématique)

Projet du tronc commun de 42 (École 42), réalisé en équipe de 3. L'objectif : reproduire le comportement de `bash` sur son cœur fonctionnel — lecture de commande, parsing, pipes, redirections, gestion des built-ins et des variables d'environnement — en C, avec `malloc`/`free` manuels et sans aucune fuite mémoire ni segfault tolérés.

Le vrai défi n'est pas de "faire marcher une commande", mais de gérer correctement les cas limites qu'un shell doit absorber en permanence : quotes imbriquées, expansion de variables au milieu d'un mot, pipelines de N commandes avec heredocs, Ctrl-C au milieu d'un `read`, fuites mémoire sur les early-exit... Le tout validé avec Valgrind (`--leak-check=full --trace-children=yes`) sur un shell interactif à processus multiples.

## 🚀 Fonctionnalités clés

- **Parsing complet en ligne de commande** : tokenizer maison (mots, opérateurs, quotes simples/doubles, espaces), fusion de tokens et détection d'erreurs de syntaxe (`|` mal placé, redirection sans cible, quotes non fermées).
- **Expansion de variables** : `$VAR`, `$?` (dernier code de sortie), expansion à l'intérieur des mots et re-split du résultat, avec respect des quotes (pas d'expansion entre `'...'`).
- **Pipelines à N commandes** (`cmd1 | cmd2 | ... | cmdN`) via une liste chaînée de commandes, un `fork()` par étage et un enchaînement de pipes.
- **Redirections** : `<`, `>`, `>>` et heredoc `<<` (avec fichier temporaire, lecture ligne par ligne, et interruption propre sur Ctrl-C).
- **7 built-ins réimplémentés** sans passer par `execve` : `cd` (avec gestion de `OLDPWD`/`PWD`), `echo` (option `-n`), `env`, `export` (avec tri alphabétique et validation d'identifiants), `unset`, `exit` (codes de sortie, `exit` avec argument non numérique), `pwd`.
- **Résolution de PATH** et exécution de commandes externes avec les mêmes messages d'erreur que bash (`command not found`, `Is a directory`, `No such file or directory`, `Permission denied`).
- **Gestion des signaux** fidèle à bash : `Ctrl-C` réaffiche le prompt et met `$?` à 130, `Ctrl-\` ignoré en mode interactif, `Ctrl-C` pendant un heredoc l'interrompt proprement.
- **Environnement synchronisé** : variables d'env maintenues en liste chaînée et re-projetées en `char **` pour `execve`, gestion de `SHLVL`.
- **Zéro fuite mémoire** : chaque structure (tokens, commandes, listes de fichiers, env) a sa fonction de libération dédiée, testée sous Valgrind avec suppressions dédiées à `readline`.

## 🧠 Notions techniques & Compétences démontrées

- **Architecture / Patterns** : pipeline de compilation façon interpréteur (lexer → parser/AST maison → exécuteur), listes doublement chaînées génériques pour tokens / commandes / fichiers / environnement, séparation stricte des responsabilités par module (`parsing/`, `exec/`, `memory/`, `signals/`, `builtins/`...).
- **Systèmes / C bas niveau** : `fork`/`execve`/`waitpid`, gestion de pipe (`pipe`, `dup2`) pour chaîner un nombre arbitraire de processus, redirections de descripteurs de fichiers, `sigaction` pour un contrôle fin des signaux (au lieu de `signal()`), fichiers temporaires pour les heredocs.
- **Gestion mémoire manuelle** : pas de garbage collector — chaque allocation a un chemin de libération explicite, y compris sur les sorties anticipées (`free_and_exit`), validé sans fuite ni descripteur orphelin sous Valgrind (`--track-fds=yes`).
- **Parsing & compilateurs (mini)** : tokenisation caractère par caractère, machine à états pour les quotes, expansion de variables avec re-découpage en mots, détection d'erreurs de syntaxe avant exécution.
- **Stack & Outils** : C99, GNU Readline (historique + édition de ligne), `libft` (implémentation maison de fonctions type libc + listes chaînées), Makefile modulaire multi-dossiers avec compilation incrémentale (`-MMD -MP`), Valgrind.
- **Rigueur de code** : conformité à la Norme 42 (fonctions ≤ 25 lignes, pas de boucles `for`, un point de retour, etc.), travail en équipe sur un dépôt Git partagé (co-développement à 2 sur des modules distincts).

## 🏗️ Architecture & Flux de données

```
readline()  →  validation syntaxique (quotes, ligne vide)
            →  Lexer (srcs/parsing/)       : découpe en tokens typés (mot, opérateur, quote, espace)
            →  Expansion (srcs/parsing/)   : remplace $VAR / $? dans les tokens, re-split le résultat
            →  Builder (srcs/parsing/)     : assemble les tokens en liste chaînée de t_cmd_node
                                              (une commande par étage de pipeline, avec ses
                                              redirections attachées sous forme de t_filelist)
            →  Exécution (srcs/exec/)      : heredocs préparés en amont,
                                              puis soit exec_simple_cmd (une commande),
                                              soit exec_pipe (fork + pipe() en chaîne pour N commandes)
            →  Nettoyage (srcs/memory/)    : libération des listes, fermeture des fd, suppression
                                              des fichiers temporaires de heredoc
```

Chaque commande du pipeline connaît son type via un système de flags bitwise (`PIPE`, `REDIRECT_IN`, `HEREDOC`, `REDIRECT_OUT`, `APPEND`, `EXTERN`, `BUILTIN`), ce qui permet de router l'exécution (built-in vs `execve`, avec ou sans redirection) sans dupliquer la logique.

## 🛠️ Installation & Quickstart

Prérequis : `gcc`/`cc`, `make`, et la lib de développement de `readline` (`libreadline-dev` sur Debian/Ubuntu, `readline` via Homebrew sur macOS).

```bash
git clone <repo>
cd minishell
make            # compile libft puis minishell
./minishell
```

Autres cibles utiles :

```bash
make clean      # supprime les .o
make fclean     # supprime aussi le binaire et libft.a
make re         # fclean + all
make vallog     # build + exécution sous Valgrind (fuites + fd + sous-processus), log dans valgrind.log
```
