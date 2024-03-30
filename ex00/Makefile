# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 14:06:15 by gbrunet           #+#    #+#              #
#    Updated: 2024/03/30 22:57:49 by gbrunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_BLACK = \033[0;30m
_RED = \033[0;31m
_GREEN = \033[0;32m
_BLUE = \033[0;34m
_YELLOW = \033[0;33m
_PURPLE = \033[0;35m
_CYAN = \033[0;36m
_WHITE = \033[0;37m

_BOLD = \033[1m
_THIN = \033[2m

_END = \033[0m

NAME = btc

CC = c++

INCLUDES = includes

CFLAGS = -Wall -Wextra -Werror -std=c++98 -I $(INCLUDES)

SRC_DIR = sources/

OBJ_DIR = objects/

SRC = main BitcoinExchange BitcoinExchange_print BitcoinExchange_utils

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

COMPTEUR = 0

.PHONY : all clean fclean re

all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(eval COMPTEUR=$(shell echo $$(($(COMPTEUR)+1))))
	@mkdir -p $(@D)
	@printf "$(_CYAN)Binary $(COMPTEUR): $@$(_END)\n"
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME) : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME)
	@echo "$(_GREEN)$(NAME) created.$(_END)"

clean :
	@echo "$(_YELLOW)$(NAME): Clean...$(_END)"
	$(RM) -rf $(OBJ_DIR)
	@echo "$(_GREEN)$(NAME): Binaries deleted.$(_END)"

fclean :
	@echo "$(_YELLOW)$(NAME): Full clean...$(_END)"
	$(RM) -rf $(OBJ_DIR)
	@echo "$(_GREEN)$(NAME): Binaries deleted.$(_END)"
	$(RM) $(NAME)
	@echo "$(_GREEN)$(NAME) deleted.$(_END)"

re :
	@make fclean --no-print-directory
	@make all --no-print-directory
