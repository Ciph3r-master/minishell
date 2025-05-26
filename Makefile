NAME = minishell

CC = cc

FLAGS_C = -Wall -Wextra -Werror -MMD -MP -I./includes
FLAGS_DEP = -MMD -MP
FLAGS_INC = -I./includes
FLAGS = $(C_FLAGS) $(DEP_FLAGS) $(INC_FLAGS)

DIR_OBJS = ./objs
DIR_SRCS = ./srcs

DIR_CORE = $(DIR_SRCS)/core
DIR_PARSING = $(DIR_SRCS)/parsing

SRCS =							\
	$(DIR_CORE)/minishell.c 	\
	$(DIR_PARSING)/quotes.c		\

OBJS_CORE = $(SRC:$(DIR_CORE)/%.c=$(DIR_OBJS)/%.o)
OBJS_PARSING = $(SRC:$(DIR_CORE)/%.c=$(DIR_OBJS)/%.o)

OBJS_DEPS = $(SRC:$(DIR_PARSING)/%.c=$(DIR_OBJS)/%.d)

OBJS =


all: $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	mkdir -p $(DIR_OBJS)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

-include $(DEPS)

clean:
	rm -rf $(DIR_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
