/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:35 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/10 16:14:45 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termcap.h>
# include "../libft/libft.h"


//**********ENUM**************/
typedef enum
{
	COMMANDES = 1,
	OPTIONS = 2,
	ARGUMENTS = 3,
	OPERATORS = 4,
	FILES = 5,
	QUOTES = 6,
	APPEND = 7
} My_first_enum;

//*********STRUCTURES*********/
typedef struct s_lst_arg
{
	int					index;
	char				*rl_arg;
	int					type;
	struct s_lst_arg	*next;
	struct s_lst_arg	*prev;
}	t_lst_arg;

typedef struct s_data
{
	char		**rl_tab;
	char		**tab_env;//copie de envp//
	int			tab_len;
	t_lst_arg	*rl_lst;
	t_lst_arg	*ws_lst;
}	t_data;





//*********SOURCES*********?/
//**********MAIN.C************/
int			main(int argc, char **argv, char **envp);

//**********LST_UTILS.C*******/
void		rl_lst_addback(t_lst_arg **lst, t_lst_arg *new);
t_lst_arg	*rl_lst_new(char *start, char *str, int i);
void		rl_lst_clear(t_lst_arg **lst);
void		rl_lst_addfront(t_lst_arg **lst, t_lst_arg *new);

//**********TOKENIZE.C****/
void	tokenize(char *str, t_lst_arg **token);
int	is_whitespace(char c);

//**********FILL_SUPREM_KNOWLEDGE.C****/
void	init_suprem_knowledge(t_data **s_k, char **envp);
void free_data(t_data **s_k);
void	fill_suprem_knowledge(t_data **s_k, char *str);
void	fill_s_k_tab(t_data **s_k, char *str);

//**********UTILS.C****/
int	count_words(const char *str);
void	copy_word(char *dest, char **src);
void	free_tab(char **tab);

//**********FILL_TAB_ENV.C****/
void	fill_tab_env(t_data **s_k, char **envp);








#endif