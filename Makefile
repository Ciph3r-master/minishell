# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qutruche <qutruche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 19:23:55 by thibaud           #+#    #+#              #
#    Updated: 2025/06/03 18:50:14 by qutruche         ###   ########.fr        #
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

CFLAGS       := -Wall -Wextra -Werror -MMD -MP -I./includes -I./libft $(READLINE_INC)
LDFLAGS      := $(READLINE_LIB) -lreadline

# === Libraries ===

DIR_LIBFT = ./libft
A_LIBFT = ./libft/libft.a

# === Directories ===

DIR_SRCS     := srcs
DIR_CORE     := $(DIR_SRCS)/core
DIR_PARSING  := $(DIR_SRCS)/parsing
DIR_OBJS     := .objs

# === Source Files ===

SRCS_CORE    :=				\
	$(DIR_CORE)/minishell.c

SRCS_PARSING :=				\
	$(DIR_PARSING)/quotes.c \
	$(DIR_PARSING)/token.c

SRCS         := $(SRCS_CORE) $(SRCS_PARSING)

# === Object Files ===

OBJS_CORE    := $(SRCS_CORE:$(DIR_CORE)/%.c=$(DIR_OBJS)/%.o)
OBJS_PARSING := $(SRCS_PARSING:$(DIR_PARSING)/%.c=$(DIR_OBJS)/%.o)
OBJS         := $(OBJS_CORE) $(OBJS_PARSING)

# === Dependencies ===

DEPS         := $(OBJS:.o=.d)

# === Rules ===
all: lib
	@echo "$(COLOR_GREEN)==> Compilation de $(NAME)...$(COLOR_RESET)"
	$(MAKE) $(NAME)

lib:
	@echo "$(COLOR_GREEN)==> Compilation de libft...$(COLOR_RESET)"
	$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJS)/%.o: $(DIR_CORE)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_PARSING)/%.c
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
