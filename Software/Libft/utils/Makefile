# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/05 14:49:36 by pvital-m          #+#    #+#              #
#    Updated: 2023/10/25 15:09:16 by pedromota        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= @cc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address,undefined
LIB1	= @ar -rcs
LIB2	= @ranlib
RM		= @/bin/rm -f

NAME	= libft.a



SRCS	= 	./src/ft_isalpha.c ./src/ft_isdigit.c ./src/ft_isalnum.c ./src/ft_isascii.c \
			./src/ft_isprint.c ./src/ft_strlen.c ./src/ft_memset.c ./src/ft_bzero.c	\
			./src/ft_memcpy.c ./src/ft_memmove.c ./src/ft_strlcpy.c ./src/ft_strlcat.c \
			./src/ft_toupper.c ./src/ft_tolower.c ./src/ft_strchr.c ./src/ft_strrchr.c \
			./src/ft_strncmp.c ./src/ft_memchr.c ./src/ft_memcmp.c ./src/ft_strnstr.c \
			./src/ft_atoi.c ./src/ft_calloc.c ./src/ft_strdup.c ./src/ft_substr.c \
			./src/ft_strjoin.c ./src/ft_strtrim.c ./src/ft_split.c ./src/ft_itoa.c \
			./src/ft_strmapi.c ./src/ft_striteri.c ./src/ft_putchar_fd.c \
			./src/ft_putstr_fd.c ./src/ft_putendl_fd.c ./src/ft_putnbr_fd.c \
			./src/get_next_line_bonus.c ./src/get_next_line_utils_bonus.c \
			./src/ft_addr.c ./src/ft_hex.c ./src/ft_int.c ./src/ft_print_chr.c \
			./src/ft_printf.c ./src/ft_strcmp.c
			
			
OBJS	= $(SRCS:.c=.o)

BONUS_S	= 	./src/ft_lstnew.c ./src/ft_lstadd_front.c ./src/ft_lstsize.c ./src/ft_lstlast.c \
			./src/ft_lstadd_back.c ./src/ft_lstdelone.c ./src/ft_lstclear.c ./src/ft_lstiter.c \
			./src/ft_lstmap.c
			
BONUS_O	= $(BONUS_S:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			@printf "\033[0;32mLBFT: \033[0;33mCreating library...\033[0m\n"
			$(LIB1) $(NAME) $(OBJS)
			$(LIB2) $(NAME)

bonus:		$(NAME) $(BONUS_O)
			$(LIB1) $(NAME) $(BONUS_O)
			$(LIB2) $(NAME)

%.o : %.c
			$(CC) -I ../ -c $< -o $(<:.c=.o)

clean:
			$(RM) $(OBJS) $(BONUS_O)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all


upload:
			git add .
			git commit -m "upload"
			git push