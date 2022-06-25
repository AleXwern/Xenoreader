# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 23:38:19 by AleXwern          #+#    #+#              #
#    Updated: 2022/06/12 01:20:58 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
FLAG	= -m64 -no-pie -Wall -Wextra -Werror
SRC		= wordwrap_test.cpp romannumerals_test.cpp primefactors_test.cpp
TEST	= $(addprefix ./build/,$(TESTS))
OBJ		= $(addprefix ./obj/,$(SRC:.c=.o))
LIBFT	= Libft_ASM.a
INCLS	= -I ./includes
GREEN	= \033[0;32m
PURPLE	= \033[0;35m
STOP	= \033[0m
TEMP0	= 0

.PHONY: all clean fclean re libft

all: $(NAME)

./obj/%.o:./tests/%.c
	@echo "Compiling $(GREEN)$@$(STOP)"
	@mkdir -p obj
	@g++ $(FLAG) -c $< -o $@ $(INCLS)

libft:
	@make -C libft_asm objonly
	@make -C libftc
	@make -C ft_malloc
	@make -C libax
	@make -C libgfx

$(NAME): libft
	@echo "Building $(PURPLE)Libft$(STOP) libraries"
	@mkdir -p build
	@cp libftc/libft.a build
	@cp libftc/includes/* includes
	@cp libax/libax.a build
	@cp libax/includes/* includes
	@cp libgfx/libgfx.a build
	@cp libgfx/includes/* includes
	@cp ft_malloc/libft_malloc.so build
	@cp ft_malloc/includes/* includes

clean:
	@/bin/rm -rf ./obj
	@make -C libft_asm clean
	@make -C ft_malloc clean
	@make -C libgfx clean
	@make -C libax clean
	@make -C libftc clean

fclean: clean
	@/bin/rm -rf ./build
	@make -C libft_asm fclean
	@make -C ft_malloc fclean
	@make -C libgfx fclean
	@make -C libax fclean
	@make -C libftc fclean

re: fclean all
