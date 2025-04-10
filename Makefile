# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: quentin <quentin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 08:15:59 by qumiraud          #+#    #+#              #
#    Updated: 2025/04/10 12:27:16 by quentin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRC = 	srcs/main/main.c\
		srcs/utils/lst_utils.c\
		srcs/utils/utils.c\
		srcs/parsing/tokenize.c\
		srcs/parsing/fill_suprem_knowledge.c\


INC = includes

OBJ_DIR = .obj
OBJ = $(SRC:srcs/%/%.c=$(OBJ_DIR)/%.o)


LIBS = libft
LIBFT = libft/libft.a

GREEN =\033[0;32m
RED =\033[0;31m
END =\033[0m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -L$(LIBS) -lft -o $@  -lreadline
	@echo "$(GREEN)success$(END)"

$(LIBFT):
	@$(MAKE) -C $(LIBS)

$(OBJ_DIR)/%.o: srcs/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC) -I$(LIBS) -o $@ -c $<
	@echo "Compiling $(notdir $<) ..."

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) -C $(LIBS) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)all objects from $(NAME) successfully removed\n $(END)"

fclean: clean
	@echo "cleaning libraries and executable..."
	@$(MAKE) -C $(LIBS) fclean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) successfully removed\n $(END)"

re: fclean all

.PHONY: all clean fclean re