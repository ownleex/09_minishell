# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 21:28:06 by ayarmaya          #+#    #+#              #
#    Updated: 2024/09/02 01:41:59 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:= minishell

CC					:= gcc
CFLAGS				:= -g -Wall -Wextra -Werror
RM					:= rm -f
RMDIR				:= rm -rf

LIBFT				:= libft/libft.a

UNAME_S				:= $(shell uname -s)

HEADERS				:= -I./include -Ilibft/include
LIBS				:= $(LIBFT) -lreadline -ltermcap

ifeq ($(UNAME_S), Darwin)
    READLINE_PATH	:= $(shell brew --prefix readline)
    HEADERS			+= -I$(READLINE_PATH)/include
    LIBS			+= -L$(READLINE_PATH)/lib
endif

SRCDIR				:= src
SRCS				:= $(shell find $(SRCDIR) -name '*.c')

OBJDIR				:= obj
OBJS				:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all					: $(NAME)

$(NAME)				: $(OBJS)
		make -C libft
		$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o		: $(SRCDIR)/%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
		$(RMDIR) $(OBJDIR)
		make -C libft clean

fclean				: clean
		$(RM) $(NAME)
		make -C libft fclean

re					: fclean all

.PHONY				: all clean fclean re
