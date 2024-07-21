# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlebecq <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 23:18:50 by xlebecq           #+#    #+#              #
#    Updated: 2024/06/25 23:21:37 by xlebecq          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -f

HEADER_DIR= ./header/

SRC_DIR = ./src/

SRC = $(addprefix $(SRC_DIR), $(C_FILES))

C_FILES = main.c

OBJ = $(SRC:.c=.o)

OBJ_DIR = $(addprefix $(OBJ_PATH), $(OBJ))

LIB_DIR = ./lib/

LIB = $(LIB_DIR)lib.a


INCLUDES = -I$(LIB_DIR) -I$(HEADER_DIR)

OBJ_PATH = .obj/

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

lib2:
	@make -C $(LIB_DIR) --no-print-directory


$(NAME): lib2 $(OBJ)
	@$(CC) $(OBJ)  $(LIB) -o $(NAME)
	@echo "${GREEN}Build successful!${RESET}"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "${GREEN}Compiled $<${RESET}"

clean:
	@$(MAKE) -C $(LIB_DIR) fclean --no-print-directory
	@$(RM) $(OBJ)
	@echo "${GREEN}Cleaned all object files.${RESET}"

fclean: clean
	@$(RM) $(NAME)
	@echo "${GREEN}Fully cleaned project.${RESET}"

re: fclean all

.PHONY: all clean fclean re
