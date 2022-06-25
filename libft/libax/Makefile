# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 11:06:06 by anystrom          #+#    #+#              #
#    Updated: 2022/06/12 01:10:21 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libax.a
FLAG	= -m64 -no-pie -Wall -Wextra -Werror
SRC		= ax_init.c ax_open.c ax_resolve.c ax_send.c ax_printip.c
OBJ		= $(addprefix ./obj/,$(SRC:.c=.o))
INCLS	= -I ./includes -I ../libftc/includes
OBJFLD	= ../obj/
GREEN	= \033[0;32m
PURPLE	= \033[0;35m
STOP	= \033[0m

.PHONY: all clean fclean re

all: $(NAME)

./obj/%.o:./src/%.c
	@echo "Compiling $(GREEN)$@$(STOP)"
	@mkdir -p obj
	@gcc $(FLAG) $(INCLS) -o $@ -c $<

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Compiled $(PURPLE)$(NAME)$(STOP)"

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf ./obj

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
