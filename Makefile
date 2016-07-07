# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sduprey <sduprey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/17 05:35:05 by sduprey           #+#    #+#              #
#    Updated: 2016/07/07 03:13:42 by bhenne           ###   ########.fr        #
#    Updated: 2016/07/07 02:23:54 by tlepeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC =	main.c \
	events.c \

SRCDIR = src/

OBJDIR = obj/

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

CC = clang

INC = -I ./inc -I libft/includes

LIB = -L libft -lft

FLAGS = -Wall -Werror -Wextra

RM = rm -rf

MLX_FLAGS = -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit

all: lft $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(C_FLAGS) $(MLX_FLAGS) -o $(NAME) $(LIB) $^
	@echo ""
	@echo $(PX_STR) : $(EX_STR)
	@echo ""

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(C_FLAGS) $(INC) $< -o $@
	@echo $(CC_STR) $*

lft:
	@make -C libft

clean:
	@$(RM) $(OBJDIR)
	@echo $(RM_STR) objects

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)
	@echo $(RM_STR) $(NAME)

re: fclean all

NO_COLOR = "\033[0;0m"
CC_COLOR = "\033[0;33m"
EX_COLOR = "\033[0;32m"
PX_COLOR = "\033[4;37m"
RM_COLOR = "\033[0;31m"

CC_STR = $(CC_COLOR)[CC]$(NO_COLOR)
EX_STR = $(EX_COLOR)$(NAME)$(NO_COLOR)
PX_STR = $(PX_COLOR)Binary compiled successfully$(NO_COLOR)
RM_STR = $(RM_COLOR)Remove$(NO_COLOR)
