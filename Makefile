# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sduprey <sduprey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/17 05:35:05 by sduprey           #+#    #+#              #
#    Updated: 2016/07/07 01:00:36 by sduprey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

FILES = main

SRC = $(addsuffix .c, $(FILES))

OBJ = $(addsuffix .o, $(FILES))

CC = gcc

FLAGS = -Wall -Werror -Wextra

FLAGS_MLX = -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(FLAGS_MLX) -o $(NAME) $(OBJ) -L libft/ -lft

$(OBJ):
	@make -C libft/
	@$(CC) $(FLAGS) -I includes -c $(SRC)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@make -C libft/ fclean

re: fclean all
