# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 01:58:16 by ayarmaya          #+#    #+#              #
#    Updated: 2024/01/18 05:14:12 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRC		=	src/libft/ft_bzero \
			src/libft/ft_isalnum \
			src/libft/ft_isalpha \
			src/libft/ft_isascii \
			src/libft/ft_isdigit \
			src/libft/ft_isprint \
			src/libft/ft_memcpy \
			src/libft/ft_memmove \
			src/libft/ft_strlen \
			src/libft/ft_memset \
			src/libft/ft_strlcpy \
			src/libft/ft_strlcat \
			src/libft/ft_toupper \
			src/libft/ft_tolower \
			src/libft/ft_strchr \
			src/libft/ft_strrchr \
			src/libft/ft_strncmp \
			src/libft/ft_memchr \
			src/libft/ft_memcmp \
			src/libft/ft_strnstr \
			src/libft/ft_atoi \
			src/libft/ft_calloc \
			src/libft/ft_strdup \
			src/libft/ft_substr \
			src/libft/ft_strjoin \
			src/libft/ft_strtrim \
			src/libft/ft_split \
			src/libft/ft_itoa \
			src/libft/ft_strmapi \
			src/libft/ft_striteri \
			src/libft/ft_putchar_fd \
			src/libft/ft_putstr_fd \
			src/libft/ft_putendl_fd \
			src/libft/ft_putnbr_fd \
			src/libft/ft_lstnew \
			src/libft/ft_lstadd_front \
			src/libft/ft_lstsize \
			src/libft/ft_lstlast \
			src/libft/ft_lstadd_back \
			src/libft/ft_lstdelone \
			src/libft/ft_lstclear \
			src/libft/ft_lstiter \
			src/libft/ft_lstmap \
			src/get_next_line/get_next_line \
			src/get_next_line/get_next_line_utils \
			src/ft_printf/ft_printf \
			src/ft_printf/ft_printint \
			src/ft_printf/ft_printhex \
			src/ft_printf/ft_printptr \
			src/ft_printf/ft_printstr \
			src/ft_printf/ft_printuint

SRCS		=	$(addsuffix .c, ${SRC})

OBJS		=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM		= 	rm -f

AR		= 	ar crs

all:		$(NAME)

$(NAME): 	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
