# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sduprey <sduprey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/17 05:35:05 by sduprey           #+#    #+#              #
#    Updated: 2016/07/07 01:58:21 by sduprey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

SRC = main.c \

SRCDIR = src/
OBJDIR = obj/

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

CC = clang

INC = -I ./inc -I libft/includes

LIB = -L libft -lft

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

MLXFLAGS = -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit

all: lft $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(LIB) $^

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(INC) $< -o $@


lft:
	make -C libft

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
