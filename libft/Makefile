#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: sduprey <sduprey@student.42.fr>            +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2014/11/05 19:40:58 by sduprey           #+#    #+#             *#
#*   Updated: 2015/10/06 02:04:34 by sduprey          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = libft.a

SRC = ft_putstr.c ft_putendl.c ft_putchar.c ft_putnbr.c get_next_line.c ft_bzero.c ft_memalloc.c ft_realloc.c ft_strcpy.c ft_strdup.c ft_strlen.c ft_memcpy.c ft_strchr.c ft_strstr.c ft_strsplit.c ft_strtrim.c ft_strsub.c ft_strjoin.c ft_atof.c ft_isdigit.c ft_isspace.c free_tab.c ft_epur_str.c ft_epur_str_c.c ft_strcmp.c

NO_COLOR = "\033[0;0m"
CC_COLOR = "\033[0;33m"
EX_COLOR = "\033[0;32m"
PX_COLOR = "\033[4;37m"
DE_COLOR = "\033[0;31m"

CC_STR = $(CC_COLOR)[CC]$(NO_COLOR)
EX_STR = $(EX_COLOR)$(NAME)$(NO_COLOR)
PX_STR = $(PX_COLOR)Library compiled successfully$(NO_COLOR)
DE_STR = $(DE_COLOR)Remove$(NO_COLOR)

OBJDIR = obj/
OBJ = $(SRC:%.c=$(OBJDIR)%.o)
CC = gcc
INC = -I ./includes
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $^
	@echo ""
	@echo $(PX_STR) : $(EX_STR)
	@echo ""

$(OBJDIR)%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(CFLAGS) $(INC) $< -o $@
	@echo $(CC_STR) $*

.PHONY: clean fclean

clean:
	@$(RM) $(OBJDIR)
	@echo $(DE_STR) objects

fclean: clean
	@$(RM) $(NAME)
	@echo $(DE_STR) $(NAME)

re: fclean all
