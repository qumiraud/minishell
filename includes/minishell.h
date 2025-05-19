/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:35 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/15 11:31:42 by pjurdana         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
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
	// t_lst_arg			*cmd_arg;

	char				*cmd_arg;
	int					type;
	struct s_lst_arg	*next;
	struct s_lst_arg	*prev;
}	t_lst_arg;


#define MAX_ARGS 1024


typedef struct s_cmd
{

	// char *command;
	int				argc;
	char			*args[MAX_ARGS];
	char			*input_file;
	char			*output_file;
	int				append;
	int				here_doc; // '>>' = 1 ||| '>' = 0
	int				nb_ope;
	struct	s_cmd	*next;

}				t_cmd;




typedef struct s_data
{
	char		**rl_tab;
	char		**glutto_tab;
	char		**re_token;
	char		**tab_env;//copie de envp//
	int			tab_len;
	int			pipefd1[2];
	int			pipefd2[2];
	int			pipe_nbr;
	void		*pid;
	int			stat_quo;
	int			pipe_quo;
	t_lst_arg	*rl_lst;
	t_lst_arg	*cmd_arg;
	t_lst_arg	*ws_lst;
	t_cmd		*cmd;
}	t_data;	


typedef struct s_echo_data
{
	int	i;
	int	j;
	int	n;
	int	n_def;
}	t_echo_data;	








//*********SOURCES*********?/


//**********MAIN.C*************************************************/
int			main(int argc, char **argv, char **envp);
void		print_tab(t_data *s_k);
void		print_env(t_data *s_k);
void		print_all(t_data *s_k);



//**********LST_UTILS.C********************************************/
void		rl_lst_addback(t_lst_arg **lst, t_lst_arg *new);
t_lst_arg	*rl_lst_new(char *start, char *str, int i);
void		rl_lst_clear(t_lst_arg **lst);
void		rl_lst_addfront(t_lst_arg **lst, t_lst_arg *new);






//**********TOKENIZE.C*********************************************/
void		tokenize(char *str, t_lst_arg **token);
// void		tokenize(t_data **s_k, t_lst_arg **token);
int			is_whitespace(char c);





//**********FILL_SUPREM_KNOWLEDGE.C********************************/
void		init_suprem_knowledge(t_data **s_k, char **envp);
void 		free_data(t_data **s_k);
void		fill_suprem_knowledge(t_data **s_k, char *str);
void		fill_s_k_tab(t_data **s_k, char *str);
// int			count_letters(int k, int count, char *str);
int			count_letters(char *str);





//**********GLUTTONY.C*********************************************/
int		glt_count_letters(char *str);
int		glt_count_words(const char *str);
void	fill_tabs(t_data **s_k, char *str);
void	fill_gluttony_tab(t_data **s_k, char *str);
void	glt_copy_word(char *dest, char **src, int count_l);





//**********UTILS.C************************************************/
int			count_words(const char *str);
void		copy_word(char *dest, char **src, int count_l);
void		free_tab(char **tab);

int	quote_verif(char *str, t_data **s_k);
int	pipe_quota(char *str, t_data **s_k);





//**********FILL_TAB_ENV.C*****************************************/
void		fill_tab_env(t_data **s_k, char **envp);




//**********EXEC_DIRECTORY*****************************************/
int			init_pipefd(int *pipefd);
int			handle_exec(t_data *s_k);
int			ft_exec_multipipe(t_data *s_k);
int			ft_exec_singlepipe(t_data *s_k);
int			ft_exec_nopipe(t_data *s_k);
char		*get_way(char **env, char **rl_tab);


//**********CMD_NT_FD.C********************************************/
int	cmd_nt_fd(char *str);//, t_data **s_k);



//**********SIGNALS.C**********************************************/

void	setup_signal(void);





int	re_token_wd(t_data **s_k);




void print_command_list(t_cmd *cmd_list);


t_cmd *parse_cmd(char **token);




#endif
