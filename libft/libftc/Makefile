# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 16:09:13 by anystrom          #+#    #+#              #
#    Updated: 2022/06/19 23:16:36 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
FLAG	= -m64 -no-pie -Wall -Wextra -Werror -nostdlib -DONLY_LIBFT
SRC		= ft_memalloc.c ft_putendl.c ft_strcpy.c ft_strmapi.c ft_strsub.c \
		ft_memccpy.c ft_putendl_fd.c ft_strdel.c ft_strncat.c ft_strtrim.c \
		ft_atoi.c ft_memchr.c ft_putnbr.c ft_strdup.c ft_strncmp.c \
		ft_tolower.c ft_bzero.c ft_memcmp.c ft_putnbr_fd.c ft_strequ.c \
		ft_strncpy.c ft_toupper.c ft_isalnum.c ft_memcpy.c ft_putstr.c \
		ft_striter.c ft_strnequ.c ft_isalpha.c ft_memdel.c ft_putstr_fd.c \
		ft_striteri.c ft_strnew.c ft_isascii.c ft_memmove.c ft_strcat.c \
		ft_strjoin.c ft_strnstr.c ft_isdigit.c ft_memset.c ft_strchr.c \
		ft_strlcat.c ft_strrchr.c ft_isprint.c ft_putchar.c ft_strclr.c \
		ft_strlen.c ft_strsplit.c ft_itoa.c ft_putchar_fd.c ft_strcmp.c \
		ft_strmap.c ft_strstr.c ft_wordlen.c ft_isblank.c ft_isnegative.c \
		ft_intsize.c ft_isextascii.c get_next_line.c ft_puthex.c ft_lcm.c \
		ft_abs.c ft_fabs.c ft_putnbrln.c ft_quadjoin.c \
		ft_strfjoin.c ft_printmem.c ft_putulongln.c ft_putulong.c
OBJ		= $(addprefix ./obj/,$(SRC:.c=.o))
INCLS	= -I ./includes -I ../ft_malloc/includes -I ../Libft_ASM/includes
OBJFLD	= ./obj/
GREEN	= \033[0;32m
PURPLE	= \033[0;35m
STOP	= \033[0m

.PHONY: all clean fclean re asm

all: $(NAME)

./obj/%.o:./src/%.c
	@echo "Compiling $(GREEN)$@$(STOP)"
	@mkdir -p obj
	@gcc $(FLAG) $(INCLS) -o $@ -c $<

asm:
	@mkdir -p obj
	@cp ../Libft_ASM/obj/* ./obj

$(NAME): asm $(OBJ)
	@ar rc $(NAME) $(wildcard obj/*.o)
	@ranlib $(NAME)
	@echo "Compiled $(PURPLE)$(NAME)$(STOP)"

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf ./obj

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
