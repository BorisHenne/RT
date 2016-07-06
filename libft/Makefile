# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/05 22:37:19 by tlepeche          #+#    #+#              #
#    Updated: 2015/02/27 05:16:51 by tlepeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME= libft.a

SRC= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	 ft_isprint.c ft_itoa.c ft_memalloc.c ft_memchr.c ft_memcmp.c \
	 ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
	 ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
	 ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c \
	 ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
	 ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
	 ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
	 ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
	 ft_strsub.c ft_strtrim.c ft_strtrim_x.c ft_tolower.c ft_isnumber.c\
	 ft_toupper.c ft_isspace.c ft_memccpy.c ft_realloc.c ft_strrevchr.c \
	 ft_how_many.c ft_strnchr.c free_tab.c ft_strsplit_blank.c ft_printtab.c \
	 ft_tablen.c free_tabi.c

OBJDIR= OBJ/

OBJ= $(SRC:%.c=$(OBJDIR)%.o)

CC= gcc

CFLAGS= -Wextra -Wall -Werror

RM= rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^

$(OBJDIR)%.o:%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
