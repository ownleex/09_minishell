# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 21:28:06 by ayarmaya          #+#    #+#              #
#    Updated: 2024/09/20 22:52:21 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:= minishell

CC					:= gcc
CFLAGS				:= -Wall -Wextra -Werror
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
SRCS				:= src/main.c \
					   src/init.c \
					   src/signal.c \
					   src/utils.c \
					   src/parsing/parsing.c \
					   src/parsing/command_check_1.c \
					   src/parsing/command_check_2.c \
					   src/parsing/arguments.c \
					   src/parsing/instances.c \
					   src/parsing/addons.c \
					   src/parsing/utils_1.c \
					   src/parsing/utils_2.c \
					   src/parsing/utils_3.c \
					   src/exec/exec.c \
					   src/exec/fork_and_process.c \
					   src/exec/redirection_and_pipe.c \
					   src/exec/find_command_path.c \
					   src/exec/heredoc.c \
					   src/exec/utils.c \
					   src/builtin/builtin.c \
					   src/builtin/cd.c \
					   src/builtin/echo.c \
					   src/builtin/env.c \
					   src/builtin/exit.c \
					   src/builtin/export.c \
					   src/builtin/pwd.c \
					   src/builtin/unset.c \
					   src/builtin/handle_var_env/cd_env.c \
					   src/builtin/handle_var_env/export_update_env.c \
					   src/builtin/handle_var_env/unset_remove_env_var.c \

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
