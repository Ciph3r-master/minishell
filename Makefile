# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 19:23:55 by thibaud           #+#    #+#              #
#    Updated: 2025/07/19 02:40:16 by billcipher       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# === Colors ===

COLOR_RESET := \033[0m
COLOR_GREEN := \033[1;32m
COLOR_BLUE  := \033[1;34m
COLOR_YELLOW := \033[1;33m

# === Executable ===

NAME         := minishell

# === Compiler & Flags ===

CC           := cc
UNAME        := $(shell uname)

ifeq ($(UNAME), Darwin)
	READLINE_INC := -I/opt/homebrew/opt/readline/include
	READLINE_LIB := -L/opt/homebrew/opt/readline/lib
else
	READLINE_INC :=
	READLINE_LIB :=
endif

CFLAGS       := -g -gdwarf-4 -Wall -Wextra -Werror -fdiagnostics-color=always -MMD -MP -I./includes -I./libft $(READLINE_INC)
LDFLAGS      := $(READLINE_LIB) -lreadline

# === Libraries ===

DIR_LIBFT = ./libft
A_LIBFT = ./libft/libft.a

# === Directories ===

DIR_SRCS			:= srcs
DIR_BUILTINS		:= $(DIR_SRCS)/builtins
DIR_CORE			:= $(DIR_SRCS)/core
DIR_DATA			:= $(DIR_SRCS)/data
DIR_ENV_COPY		:= $(DIR_SRCS)/env_copy
DIR_ERROR			:= $(DIR_SRCS)/error
DIR_EXEC			:= $(DIR_SRCS)/exec
DIR_MEMORY			:= $(DIR_SRCS)/memory
DIR_MESSAGE			:= $(DIR_SRCS)/message
DIR_PARSING  		:= $(DIR_SRCS)/parsing
DIR_PARSING_UTILS	:= $(DIR_SRCS)/parsing_utils
DIR_SIGNALS			:= $(DIR_SRCS)/signals
DIR_OBJS			:= .objs

# === Source Files ===

SRCS_BUILTINS	:=						\
	$(DIR_BUILTINS)/pwd.c				\
	$(DIR_BUILTINS)/echo.c				\
	$(DIR_BUILTINS)/env.c				\
	$(DIR_BUILTINS)/unset.c				\
	$(DIR_BUILTINS)/exit.c				\
	$(DIR_BUILTINS)/export.c			\
	$(DIR_BUILTINS)/export_utils.c		\
	$(DIR_BUILTINS)/cd.c		\

SRCS_CORE	:=							\
	$(DIR_CORE)/core_loop.c				\
	$(DIR_CORE)/minishell.c				\

SRCS_DATA	:=							\
	$(DIR_DATA)/init_data.c

SRCS_ENV_COPY	:=						\
	$(DIR_ENV_COPY)/env_list.c			\
	$(DIR_ENV_COPY)/get_env_copy.c		\
	$(DIR_ENV_COPY)/get_env_list.c

SRCS_ERROR	:=							\
	$(DIR_ERROR)/free_and_exit.c

SRCS_EXEC	:=								\
	$(DIR_EXEC)/builtins.c					\
	$(DIR_EXEC)/cmd_path.c					\
	$(DIR_EXEC)/create_tmp_file.c			\
	$(DIR_EXEC)/dfl_env_list.c				\
	$(DIR_EXEC)/exec_pipe.c					\
	$(DIR_EXEC)/exec.c						\
	$(DIR_EXEC)/extern.c					\
	$(DIR_EXEC)/get_env.c					\
	$(DIR_EXEC)/heredoc.c					\
	$(DIR_EXEC)/read_heredoc_fd.c			\
	$(DIR_EXEC)/redir_in_and_hd.c			\
	$(DIR_EXEC)/redir_out_and_append.c		\
	$(DIR_EXEC)/redirections.c				\
	$(DIR_EXEC)/sh_level.c

SRCS_MEMORY	:=							\
	$(DIR_MEMORY)/close_saved_fds.c		\
	$(DIR_MEMORY)/delete_tmp_files.c	\
	$(DIR_MEMORY)/free_all.c			\
	$(DIR_MEMORY)/free_env_list.c		\
	$(DIR_MEMORY)/free_env_copy.c		\
	$(DIR_MEMORY)/free_pathname.c		\
	$(DIR_MEMORY)/free_tokens.c			\
	$(DIR_MEMORY)/free_cmds_node.c		\
	$(DIR_MEMORY)/free_utils.c			\

SRCS_MESSAGE	:=							\
	$(DIR_MESSAGE)/error.c					\
	$(DIR_MESSAGE)/is_a_directory.c			\
	$(DIR_MESSAGE)/no_such_file_or_dir.c	\
	$(DIR_MESSAGE)/not_a_directory.c		\
	$(DIR_MESSAGE)/permission_denied.c		\
	$(DIR_MESSAGE)/redir_in_msg.c			\

SRCS_PARSING :=								\
	$(DIR_PARSING)/token_utils.c			\
	$(DIR_PARSING)/cmd_utils.c				\
	$(DIR_PARSING)/token_init.c				\
	$(DIR_PARSING)/cmd_node.c				\
	$(DIR_PARSING)/expand.c					\
	$(DIR_PARSING)/expand_utils.c			\
	$(DIR_PARSING)/extract_token.c			\
	$(DIR_PARSING)/set_token_type.c			\
	$(DIR_PARSING)/syntax_error.c			\
	$(DIR_PARSING)/set_token_type_cmds.c	\

SRCS_PARSING_UTILS :=				  		\
	$(DIR_PARSING_UTILS)/check_quotes.c 	\
	$(DIR_PARSING_UTILS)/tokendlist.c 		\
	$(DIR_PARSING_UTILS)/filedlist.c  		\
	$(DIR_PARSING_UTILS)/secure_strdup.c 	\
	$(DIR_PARSING_UTILS)/cmddlist.c 		\

SRCS_SIGNALS :=				  			\
	$(DIR_SIGNALS)/init_signals.c

SRCS := $(SRCS_BUILTINS) 				\
		$(SRCS_CORE) 					\
        $(SRCS_DATA)					\
        $(SRCS_ENV_COPY)				\
        $(SRCS_ERROR) 					\
        $(SRCS_EXEC) 					\
        $(SRCS_MEMORY) 					\
        $(SRCS_MESSAGE) 				\
        $(SRCS_PARSING) 				\
        $(SRCS_PARSING_UTILS)			\
        $(SRCS_SIGNALS)


# === Object Files ===

OBJS_BUILTINS		:= $(SRCS_BUILTINS:$(DIR_BUILTINS)/%.c=$(DIR_OBJS)/%.o)
OBJS_CORE			:= $(SRCS_CORE:$(DIR_CORE)/%.c=$(DIR_OBJS)/%.o)
OBJS_DATA			:= $(SRCS_DATA:$(DIR_DATA)/%.c=$(DIR_OBJS)/%.o)
OBJS_ENV_COPY		:= $(SRCS_ENV_COPY:$(DIR_ENV_COPY)/%.c=$(DIR_OBJS)/%.o)
OBJS_ERROR			:= $(SRCS_ERROR:$(DIR_ERROR)/%.c=$(DIR_OBJS)/%.o)
OBJS_EXEC			:= $(SRCS_EXEC:$(DIR_EXEC)/%.c=$(DIR_OBJS)/%.o)
OBJS_MEMORY			:= $(SRCS_MEMORY:$(DIR_MEMORY)/%.c=$(DIR_OBJS)/%.o)
OBJS_MESSAGE		:= $(SRCS_MESSAGE:$(DIR_MESSAGE)/%.c=$(DIR_OBJS)/%.o)
OBJS_PARSING 		:= $(SRCS_PARSING:$(DIR_PARSING)/%.c=$(DIR_OBJS)/%.o)
OBJS_PARSING_UTILS	:= $(SRCS_PARSING_UTILS:$(DIR_PARSING_UTILS)/%.c=$(DIR_OBJS)/%.o)
OBJS_SIGNALS		:= $(SRCS_SIGNALS:$(DIR_SIGNALS)/%.c=$(DIR_OBJS)/%.o)

OBJS := $(OBJS_BUILTINS)		\
		$(OBJS_CORE)			\
        $(OBJS_DATA)			\
        $(OBJS_ENV_COPY)		\
        $(OBJS_ERROR) 			\
        $(OBJS_EXEC) 			\
        $(OBJS_MEMORY)			\
        $(OBJS_MESSAGE)			\
        $(OBJS_PARSING)			\
        $(OBJS_PARSING_UTILS)	\
        $(OBJS_SIGNALS)

# === Dependencies ===

DEPS         := $(OBJS:.o=.d)

# === Rules ===
all: lib Makefile
	@echo "$(COLOR_GREEN)==> Compilation de $(NAME)...$(COLOR_RESET)"
	$(MAKE) $(NAME)

lib:
	@echo "$(COLOR_GREEN)==> Compilation de libft...$(COLOR_RESET)"
	$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJS)/%.o: $(DIR_BUILTINS)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_CORE)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_DATA)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_ENV_COPY)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_ERROR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_EXEC)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_MEMORY)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_MESSAGE)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_PARSING)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_PARSING_UTILS)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_SIGNALS)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(A_LIBFT) Makefile
	@echo "$(COLOR_BLUE)→ Linking $(NAME)$(COLOR_RESET)"
	$(CC) $(OBJS) $(A_LIBFT) -o $(NAME) $(LDFLAGS)

-include $(DEPS)

clean:
	@echo "$(COLOR_BLUE)→ Cleaning objects$(COLOR_RESET)"
	$(MAKE) clean -C $(DIR_LIBFT)
	rm -rf $(DIR_OBJS)

fclean: clean
	@echo "$(COLOR_BLUE)→ Removing executable$(COLOR_RESET)"
	rm -rf $(A_LIBFT)
	rm -f $(NAME)

re:
	@echo "$(COLOR_GREEN)==> Rebuilding $(NAME)...$(COLOR_RESET)"
	$(MAKE) fclean
	$(MAKE) all

valgrind: all
	valgrind --show-leak-kinds=all --show-mismatched-frees=yes --leak-check=full --trace-children=yes --track-fds=yes --suppressions="readline.supp" ./minishell

vallog: all
	valgrind --show-leak-kinds=all --leak-check=full --trace-children=yes --track-fds=yes --suppressions="readline.supp" --log-file="/home/billcipher/Documents/newminishell/valgrind.log" ./minishell

.PHONY: all clean fclean re
