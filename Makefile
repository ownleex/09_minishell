# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 21:28:06 by ayarmaya          #+#    #+#              #
#    Updated: 2024/07/29 01:47:13 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := gcc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
RMDIR := rm -rf

LIBFT := libft/libft.a

READLINE_PATH := $(shell brew --prefix readline)

HEADERS := -I./include -Ilibft/include -I$(READLINE_PATH)/include
LIBS := $(LIBFT) -L$(READLINE_PATH)/lib -lreadline -ltermcap

SRCS := src/main.c \
		src/exec/exec.c \
		src/parsing/parsing.c \
		src/builtin/builtin.c \
		src/builtin/echo.c \
		src/utils/utils.c \
		src/signal/signal.c \

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
