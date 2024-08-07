#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 18:00:37 by xlebecq           #+#    #+#              #
#    Updated: 2024/08/07 15:23:41 by xlebecq          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lib.a

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -f

HEADER = -I.

SRC_DIR = ./src/

SRC = $(addprefix $(SRC_DIR), $(C_FILE))

C_FILE = ft_split.c ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strnstr.c ft_substr.c
		
OBJ = $(SRC:.c=.o)

OBJ_PATH		= .obj/

OBJ_DIR			= $(addprefix $(OBJ_PATH), $(OBJ))


all: $(NAME)

$(NAME): $(OBJ_DIR)
	ar rcs $(NAME) $(OBJ_DIR)
		@ranlib $(NAME)

$(OBJ_PATH)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

clean:
	$(RM) $(OBJ_DIR)
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
