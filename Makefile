# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 21:28:06 by ayarmaya          #+#    #+#              #
#    Updated: 2024/07/28 23:04:56 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := gcc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
RMDIR := rm -rf

LIBFT := libft/libft.a

HEADERS := -I./include -Ilibft/include
LIBS := $(LIBFT) -lreadline

SRCS := src/main.c \
		src/exec/exec.c \
		src/parsing/parsing.c \
		src/builtin/builtin.c \
		src/builtin/echo.c \
		src/utils/utils.c \

OBJDIR := obj
OBJS := $(SRCS:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
		make -C libft
		$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o: src/%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
		$(RMDIR) $(OBJDIR)
		make -C libft clean

fclean: clean
		$(RM) $(NAME)
		make -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
