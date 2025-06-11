# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 19:23:55 by thibaud           #+#    #+#              #
#    Updated: 2025/06/10 14:28:07 by qutruche         ###   ########.fr        #
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
DIR_CORE			:= $(DIR_SRCS)/core
DIR_DATA			:= $(DIR_SRCS)/data
DIR_ENV_COPY		:= $(DIR_SRCS)/env_copy
DIR_PARSING  		:= $(DIR_SRCS)/parsing
DIR_PARSING_UTILS	:= $(DIR_SRCS)/parsing_utils
DIR_OBJS			:= .objs

# === Source Files ===

SRCS_CORE	:=				\
	$(DIR_CORE)/minishell.c

SRCS_DATA	:=				\
	$(DIR_DATA)/init_data.c

SRCS_ENV_COPY	:=				\
	$(DIR_ENV_COPY)/env_list.c	\
	$(DIR_ENV_COPY)/get_env.c

SRCS_PARSING :=						\
	$(DIR_PARSING)/quotes.c 		\
	$(DIR_PARSING)/token.c  		\
	$(DIR_PARSING)/token_utils.c

SRCS_PARSING_UTILS :=				  \
	$(DIR_PARSING_UTILS)/tokendlist.c \
	$(DIR_PARSING_UTILS)/filedlist.c

SRCS         := $(SRCS_CORE) $(SRCS_DATA) $(SRCS_ENV_COPY) $(SRCS_PARSING) $(SRCS_PARSING_UTILS)

# === Object Files ===

OBJS_CORE			:= $(SRCS_CORE:$(DIR_CORE)/%.c=$(DIR_OBJS)/%.o)
OBJS_DATA			:= $(SRCS_DATA:$(DIR_DATA)/%.c=$(DIR_OBJS)/%.o)
OBJS_ENV_COPY		:= $(SRCS_ENV_COPY:$(DIR_ENV_COPY)/%.c=$(DIR_OBJS)/%.o)
OBJS_PARSING 		:= $(SRCS_PARSING:$(DIR_PARSING)/%.c=$(DIR_OBJS)/%.o)
OBJS_PARSING_UTILS	:= $(SRCS_PARSING_UTILS:$(DIR_PARSING_UTILS)/%.c=$(DIR_OBJS)/%.o)
OBJS				:= $(OBJS_CORE) $(OBJS_DATA) $(OBJS_ENV_COPY) $(OBJS_PARSING) $(OBJS_PARSING_UTILS)

# === Dependencies ===

DEPS         := $(OBJS:.o=.d)

# === Rules ===
all: lib Makefile
	@echo "$(COLOR_GREEN)==> Compilation de $(NAME)...$(COLOR_RESET)"
	$(MAKE) $(NAME)

lib:
	@echo "$(COLOR_GREEN)==> Compilation de libft...$(COLOR_RESET)"
	$(MAKE) -C $(DIR_LIBFT)

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

$(DIR_OBJS)/%.o: $(DIR_PARSING)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_PARSING_UTILS)/%.c
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

.PHONY: all clean fclean re
