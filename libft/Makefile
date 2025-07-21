# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: billcipher <billcipher@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 22:04:08 by thibaud           #+#    #+#              #
#    Updated: 2025/07/21 02:09:17 by billcipher       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libft.a
HDRS    := libft.h
MAKEFILE:= Makefile

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#

SRCS		:= 					\
	ft_add_string_to_strings.c	\
	ft_atoi.c					\
	ft_bzero.c					\
	ft_calloc.c					\
	ft_free_tab_char_all.c		\
	ft_is_id.c		\
	ft_is_white_space.c			\
	ft_isalnum.c				\
	ft_isalpha.c				\
	ft_isascii.c				\
	ft_isdigit.c				\
	ft_isprint.c				\
	ft_itoa.c					\
	ft_memchr.c					\
	ft_memcmp.c					\
	ft_memcpy.c					\
	ft_memmove.c				\
	ft_memset.c					\
	ft_putchar_fd.c				\
	ft_putendl_fd.c				\
	ft_putnbr_fd.c				\
	ft_putstr_fd.c				\
	ft_split_set_support.c		\
	ft_split_set.c				\
	ft_split.c					\
	ft_strchr.c					\
	ft_strcmp.c					\
	ft_strdup.c					\
	ft_strndup.c				\
	ft_striteri.c				\
	ft_strjoin.c				\
	ft_strlcat.c				\
	ft_strlcpy.c				\
	ft_strlen.c					\
	ft_strmapi.c				\
	ft_strncmp.c				\
	ft_strnstr.c				\
	ft_strrchr.c				\
	ft_strtrim.c				\
	ft_substr.c					\
	ft_tolower.c				\
	ft_toupper.c

SRCS_BONUS	:=					\
	ft_lstnew_bonus.c			\
	ft_lstadd_front_bonus.c		\
	ft_lstsize_bonus.c			\
	ft_lstlast_bonus.c			\
	ft_lstadd_back_bonus.c		\
	ft_lstdelone_bonus.c		\
	ft_lstclear_bonus.c 		\
	ft_lstiter_bonus.c 			\
	ft_lstmap_bonus.c

OBJS		:= $(SRCS:%.c=%.o)

OBJS_BONUS	:= $(SRCS_BONUS:%.c=%.o)

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR			:= ar
ARFLAGS 	:= -r -c -s

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#

RM              := rm -f
MAKEFLAGS       += --no-print-directory
TOUCH			:= && touch bonus
BONUS			:= bonus

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c $(HDRS) Makefile
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

bonus: $(OBJS) $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(OBJS_BONUS) $(TOUCH)

clean:
	$(RM) $(BONUS) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
