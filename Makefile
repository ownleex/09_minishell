# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 21:28:06 by ayarmaya          #+#    #+#              #
#    Updated: 2024/08/04 03:17:38 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := gcc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
RMDIR := rm -rf

LIBFT := libft/libft.a

READLINE_PATH := $(shell brew --prefix readline)
# !!!!! à enlever avant EVAL !!!!!

HEADERS := -I./include -Ilibft/include -I$(READLINE_PATH)/include
LIBS := $(LIBFT) -L$(READLINE_PATH)/lib -lreadline -ltermcap

SRCDIR := src
SRCS := $(shell find $(SRCDIR) -name '*.c')

OBJDIR := obj
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
		make -C libft
		$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
		$(RMDIR) $(OBJDIR)
		make -C libft clean

fclean: clean
		$(RM) $(NAME)
		make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
