# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 19:23:55 by thibaud           #+#    #+#              #
#    Updated: 2025/05/26 19:31:07 by thibaud          ###   ########.fr        #
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

CFLAGS       := -Wall -Wextra -Werror -MMD -MP -I./includes $(READLINE_INC)
LDFLAGS      := $(READLINE_LIB) -lreadline

# === Directories ===

DIR_SRCS     := srcs
DIR_CORE     := $(DIR_SRCS)/core
DIR_PARSING  := $(DIR_SRCS)/parsing
DIR_OBJS     := objs

# === Source Files ===

SRCS_CORE    :=				\
	$(DIR_CORE)/minishell.c

SRCS_PARSING :=				\
	$(DIR_PARSING)/quotes.c

SRCS         := $(SRCS_CORE) $(SRCS_PARSING)

# === Object Files ===

OBJS_CORE    := $(SRCS_CORE:$(DIR_CORE)/%.c=$(DIR_OBJS)/%.o)
OBJS_PARSING := $(SRCS_PARSING:$(DIR_PARSING)/%.c=$(DIR_OBJS)/%.o)
OBJS         := $(OBJS_CORE) $(OBJS_PARSING)

# === Dependencies ===

DEPS         := $(OBJS:.o=.d)

# === Rules ===
all:
	@echo "$(COLOR_GREEN)==> Compilation de $(NAME)...$(COLOR_RESET)"
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	@echo "$(COLOR_BLUE)→ Linking $(NAME)$(COLOR_RESET)"
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(DIR_OBJS)/%.o: $(DIR_CORE)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJS)/%.o: $(DIR_PARSING)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_YELLOW)→ Compiling $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@echo "$(COLOR_BLUE)→ Cleaning objects$(COLOR_RESET)"
	rm -rf $(DIR_OBJS)

fclean: clean
	@echo "$(COLOR_BLUE)→ Removing executable$(COLOR_RESET)"
	rm -f $(NAME)

re:
	@echo "$(COLOR_GREEN)==> Rebuilding $(NAME)...$(COLOR_RESET)"
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
