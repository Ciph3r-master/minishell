# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 19:23:55 by thibaud           #+#    #+#              #
#    Updated: 2025/06/27 21:51:40 by thibaud          ###   ########.fr        #
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

CFLAGS       := -g3 -Wall -Wextra -Werror -MMD -MP -I./includes -I./libft $(READLINE_INC)
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
DIR_PARSING  		:= $(DIR_SRCS)/parsing
DIR_PARSING_UTILS	:= $(DIR_SRCS)/parsing_utils
DIR_SIGNALS			:= $(DIR_SRCS)/signals
DIR_OBJS			:= .objs

# === Source Files ===

SRCS_BUILTINS	:=						\
	$(DIR_BUILTINS)/pwd.c

SRCS_CORE	:=							\
	$(DIR_CORE)/minishell.c

SRCS_DATA	:=							\
	$(DIR_DATA)/init_data.c

SRCS_ENV_COPY	:=						\
	$(DIR_ENV_COPY)/env_list.c			\
	$(DIR_ENV_COPY)/get_env_copy.c		\
	$(DIR_ENV_COPY)/get_env_list.c

SRCS_ERROR	:=							\
	$(DIR_ERROR)/free_and_exit.c

SRCS_EXEC	:=							\
	$(DIR_EXEC)/builtins.c				\
	$(DIR_EXEC)/cmd_path.c				\
	$(DIR_EXEC)/create_tmp_file.c		\
	$(DIR_EXEC)/exec_pipe.c				\
	$(DIR_EXEC)/exec.c					\
	$(DIR_EXEC)/extern.c				\
	$(DIR_EXEC)/faker_builtin.c			\
	$(DIR_EXEC)/faker_extern.c			\
	$(DIR_EXEC)/get_env.c				\
	$(DIR_EXEC)/heredoc.c				\
	$(DIR_EXEC)/redir_in_and_hd.c		\
	$(DIR_EXEC)/redir_out_and_append.c	\
	$(DIR_EXEC)/redirections.c

SRCS_MEMORY	:=							\
	$(DIR_MEMORY)/delete_tmp_files.c	\
	$(DIR_MEMORY)/free_all.c			\
	$(DIR_MEMORY)/free_env_list.c		\
	$(DIR_MEMORY)/free_env_copy.c		\
	$(DIR_MEMORY)/free_pathname.c		\
	$(DIR_MEMORY)/free_tokens.c			\
	$(DIR_MEMORY)/free_cmds_node.c		\
	$(DIR_MEMORY)/free_utils.c			\

SRCS_PARSING :=							\
	$(DIR_PARSING)/quotes.c 			\
	$(DIR_PARSING)/token_utils.c		\
	$(DIR_PARSING)/cmd_utils.c			\
	$(DIR_PARSING)/token_init.c			\
	$(DIR_PARSING)/cmd_node.c			\
	$(DIR_PARSING)/expand.c				\
	$(DIR_PARSING)/extract_token.c		\
	$(DIR_PARSING)/set_token_type.c		\
	$(DIR_PARSING)/syntax_error.c		\

SRCS_PARSING_UTILS :=				  \
	$(DIR_PARSING_UTILS)/tokendlist.c \
	$(DIR_PARSING_UTILS)/filedlist.c  \
	$(DIR_PARSING_UTILS)/cmddlist.c  \

SRCS_SIGNALS :=				  			\
	$(DIR_SIGNALS)/init_signals.c

SRCS := $(SRCS_BUILTINS) 				\
		$(SRCS_CORE) 					\
        $(SRCS_DATA)					\
        $(SRCS_ENV_COPY)				\
        $(SRCS_ERROR) 					\
        $(SRCS_EXEC) 					\
        $(SRCS_MEMORY) 					\
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

$(NAME): $(OBJS) $(A_LIBFT)
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
	valgrind --show-leak-kinds=all --leak-check=full --trace-children=yes --track-fds=yes --suppressions="readline.supp" --log-file="valgrind.log" ./minishell

.PHONY: all clean fclean re
