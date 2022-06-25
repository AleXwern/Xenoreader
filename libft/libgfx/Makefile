# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 15:01:27 by AleXwern          #+#    #+#              #
#    Updated: 2020/11/16 15:01:27 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libgfx.a
FLAG	= -m64 -no-pie -Wall -Wextra -Werror
SRCFILE	= bmp.c
# obj_parse.c obj_util.c obj_vert.c obj.c
SRC		= $(addprefix ./src/,$(SRCFILE))
OBJ		= $(addprefix ./obj/,$(SRCFILE:.c=.o))
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

objonly: $(OBJ)

$(NAME): $(OBJ)
	@echo "Building $(PURPLE)$@$(STOP)"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo done

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf ./obj

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
