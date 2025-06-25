# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 08:15:59 by qumiraud          #+#    #+#              #
#    Updated: 2025/06/25 20:01:00 by qumiraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

SRC =	srcs/main/main.c\
		srcs/main/main_bis.c\
		srcs/main/main_bis_2.c\
		srcs/main/handle_readline.c\
		srcs/main/print_test.c\
		srcs/utils/lst_utils.c\
		srcs/utils/utils.c\
		srcs/utils/utils_2.c\
		srcs/utils/utils_free.c\
		srcs/utils/verif.c\
		srcs/utils/str_errors.c\
		srcs/parsing/tokenize.c\
		srcs/parsing/fill_s_k_files/fill_suprem_knowledge.c\
		srcs/parsing/fill_s_k_files/s_k_letters.c\
		srcs/parsing/fill_s_k_files/s_k_letters_2.c\
		srcs/parsing/fill_s_k_files/s_k_letters_3.c\
		srcs/parsing/fill_s_k_files/s_k_words.c\
		srcs/parsing/fill_s_k_files/s_k_words_2.c\
		srcs/parsing/fill_tab_env.c\
		srcs/exec/ft_exec.c\
		srcs/exec/multipipe.c\
		srcs/exec/singlepipe.c\
		srcs/exec/nopipe.c\
		srcs/exec/no_pipe_utils.c\
		srcs/exec/pathway.c\
		srcs/exec/utils_exec.c\
		srcs/parsing/gluttony_files/glt_letters.c\
		srcs/parsing/gluttony_files/glt_letters_2.c\
		srcs/parsing/gluttony_files/glt_words.c\
		srcs/parsing/gluttony_files/glt_words_2.c\
		srcs/parsing/gluttony_files/gluttony.c\
		srcs/parsing/gluttony_files/gluttony_2.c\
		srcs/parsing/cmd_nt_fd.c\
		srcs/parsing/tokens_to_list.c\
		srcs/parsing/tokens_to_list_2.c\
		srcs/signals/signals.c\
		srcs/builtin/echo.c\
		srcs/builtin/echo_handler.c\
		srcs/builtin/cd.c\
		srcs/builtin/cd_handler.c\
		srcs/builtin/pwd.c\
		srcs/builtin/export.c\
		srcs/builtin/export_handler.c\
		srcs/builtin/unset.c\
		srcs/builtin/env.c\
		srcs/builtin/exit.c\




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
