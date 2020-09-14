# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 16:09:13 by anystrom          #+#    #+#              #
#    Updated: 2020/08/03 16:06:07 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = xenord
FLG =
SRCFILE = main.c
SRC = $(addprefix ./src/,$(SRCFILE))
LIBFT = ./libft/libft.a
OBJ = $(SRC:.c=.o)
INCL = -I ./libft
MLXLIB = -L /usr/X11/lib/
FRAMEWORK = -lmlx -lXext -lX11 -framework OpenGL -framework AppKit

.PHONY: all clean fclean re git gitrm testcomp

all: $(NAME)

$(LIBFT):
	@make -C ./libft

%.o:%.c
	gcc $(FLG) -I ./ -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLG) $(INCL) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	/bin/rm -f $(OBJ)
	make -C ./libft clean

fclean: clean gitrm
	/bin/rm -f $(NAME)
	make -C ./libft fclean

git:
	git clone https://github.com/AleXwern/fillit-tests.git tests
	mv ./tests/maps ./
	rm -rf tests/

gitrm:
	/bin/rm -rf maps
	/bin/rm -rf tests

re: fclean all
