# Minishell

> A POSIX shell written in pure C (~4000 lines), with zero parsing libraries: lexer, pipeline, redirections and signal handling all built from scratch.

## 🎯 Why this project? (Context & Problem)

Core-curriculum project at 42 (École 42), built by a team of 2. The goal: reproduce `bash`'s core behavior — reading a command line, parsing it, pipes, redirections, built-ins and environment variables — in C, with manual `malloc`/`free` and zero tolerance for memory leaks or segfaults.

The real challenge isn't getting one command to run, it's correctly handling the edge cases a shell has to absorb constantly: nested quotes, variable expansion in the middle of a word, N-command pipelines with heredocs, Ctrl-C in the middle of a `read`, memory leaks on early exits... All of it validated with Valgrind (`--leak-check=full --trace-children=yes`) on an interactive, multi-process shell.

## 🚀 Key Features

- **Full command-line parsing**: a hand-written tokenizer (words, operators, single/double quotes, whitespace), token merging, and syntax-error detection (misplaced `|`, redirection with no target, unclosed quotes).
- **Variable expansion**: `$VAR`, `$?` (last exit status), expansion inside words with re-splitting of the result, and quote-awareness (no expansion inside `'...'`).
- **N-command pipelines** (`cmd1 | cmd2 | ... | cmdN`) via a linked list of commands, one `fork()` per stage, and chained pipes.
- **Redirections**: `<`, `>`, `>>` and heredoc `<<` (backed by a temp file, line-by-line reading, and clean interruption on Ctrl-C).
- **7 built-ins reimplemented** without going through `execve`: `cd` (with `OLDPWD`/`PWD` handling), `echo` (`-n` option), `env`, `export` (alphabetically sorted, identifier validation), `unset`, `exit` (exit codes, non-numeric argument handling), `pwd`.
- **PATH resolution** and external command execution with the same error messages as bash (`command not found`, `Is a directory`, `No such file or directory`, `Permission denied`).
- **Signal handling** faithful to bash: `Ctrl-C` redisplays the prompt and sets `$?` to 130, `Ctrl-\` is ignored in interactive mode, `Ctrl-C` during a heredoc interrupts it cleanly.
- **Synchronized environment**: env variables kept in a linked list and re-projected into a `char **` for `execve`, with `SHLVL` handling.
- **Zero memory leaks**: every structure (tokens, commands, file lists, env) has its own dedicated free function, tested under Valgrind with dedicated `readline` suppressions.

## 🧠 Technical Concepts & Skills Demonstrated

- **Architecture / Patterns**: an interpreter-style pipeline (lexer → hand-built parser/AST → executor), generic doubly-linked lists for tokens / commands / files / environment, strict separation of concerns by module (`parsing/`, `exec/`, `memory/`, `signals/`, `builtins/`...).
- **Systems / low-level C**: `fork`/`execve`/`waitpid`, pipe management (`pipe`, `dup2`) to chain an arbitrary number of processes, file descriptor redirection, `sigaction` for fine-grained signal control (instead of `signal()`), temp files for heredocs.
- **Manual memory management**: no garbage collector — every allocation has an explicit free path, including on early exits (`free_and_exit`), validated leak-free and with no orphaned file descriptors under Valgrind (`--track-fds=yes`).
- **Parsing & mini-compiler concepts**: character-by-character tokenization, a state machine for quote handling, variable expansion with word re-splitting, syntax-error detection before execution.
- **Stack & Tools**: C99, GNU Readline (history + line editing), `libft` (a hand-built libc-style function library plus linked-list utilities), a modular multi-directory Makefile with incremental compilation (`-MMD -MP`), Valgrind.
- **Code discipline**: compliant with the 42 Norm (functions ≤ 25 lines, no `for` loops, single return point, etc.), collaborative work on a shared Git repo (co-developed by 2 across distinct modules).

## 🏗️ Architecture & Data Flow

```
readline()  →  syntax validation (quotes, empty line)
            →  Lexer (srcs/parsing/)       : splits input into typed tokens (word, operator, quote, space)
            →  Expansion (srcs/parsing/)   : replaces $VAR / $? inside tokens, re-splits the result
            →  Builder (srcs/parsing/)     : assembles tokens into a linked list of t_cmd_node
                                              (one command per pipeline stage, with its
                                              redirections attached as a t_filelist)
            →  Execution (srcs/exec/)      : heredocs are prepared upfront, then either
                                              exec_simple_cmd (single command)
                                              or exec_pipe (fork + chained pipe() for N commands)
            →  Cleanup (srcs/memory/)      : frees all lists, closes file descriptors, deletes
                                              heredoc temp files
```

Each pipeline command knows its type through a bitwise flag system (`PIPE`, `REDIRECT_IN`, `HEREDOC`, `REDIRECT_OUT`, `APPEND`, `EXTERN`, `BUILTIN`), which routes execution (built-in vs `execve`, with or without redirection) without duplicating logic.

## 🛠️ Installation & Quickstart

Requirements: `gcc`/`cc`, `make`, and the `readline` development library (`libreadline-dev` on Debian/Ubuntu, `readline` via Homebrew on macOS).

```bash
git clone <repo>
cd minishell
make            # builds libft, then minishell
./minishell
```

Other useful targets:

```bash
make clean      # remove .o files
make fclean     # also remove the binary and libft.a
make re         # fclean + all
make vallog     # build + run under Valgrind (leaks + fds + subprocesses), logged to valgrind.log
```
