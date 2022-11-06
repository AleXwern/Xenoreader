# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 16:09:13 by anystrom          #+#    #+#              #
#    Updated: 2022/11/06 17:52:53 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= xenord.exe
FLAG	= -g
LIBFT	= Libft/build/libft.a
# Libft/ft_malloc/libft_malloc_x86_64.so
INCLUDES= -I includes -I Libft/includes
LIBS	= -pthread
VPATH	= src
OBJS	= obj
SRC		= $(wildcard src/*.cpp)
OBJ		= $(addprefix $(OBJS)/,$(notdir $(SRC:.cpp=.o)))
GREEN	= \033[0;32m
PURPLE	= \033[0;35m
STOP	= \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	@make -C Libft

$(OBJS)/%.o: %.cpp
	@mkdir -p $(@D)
	@g++ $(FLAG) -g $(INCLUDES) -c $< -o $@
	@echo "Compiling $(GREEN)$@$(STOP)"

$(NAME): $(LIBFT) $(OBJ)
	@echo "Building $(PURPLE)$@$(STOP)"
	@g++ $(FLAG) -o $(NAME) $(INCLUDES) $(OBJ) $(LIBFT) $(LIBS)

clean:
	/bin/rm -rf $(OBJ)
	make -C Libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C Libft fclean

re: fclean all
