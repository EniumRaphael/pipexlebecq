# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 23:18:50 by xlebecq           #+#    #+#              #
#    Updated: 2024/08/07 15:36:58 by rparodi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = ./src/

SRC = $(addprefix $(SRC_DIR), $(C_FILES))

HEADER_DIR = ./header/

RM = rm -f

C_FILES = main.c utils.c

OBJ = $(SRC:.c=.o)

LIB_DIR = ./lib/

LIB = $(LIB_DIR)lib.a

INCLUDES = -I$(HEADER_DIR) -I$(LIB_DIR)


all: $(NAME)

lib2:
	make -C $(LIB_DIR)

$(NAME): lib2 $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	$(MAKE) -C $(LIB_DIR) fclean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
