/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:35 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 11:27:57 by qumiraud         ###   ########.fr       */
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

extern int	g_status;

//*********STRUCTURES*********/
typedef struct s_lst_arg
{
	int					index;
	char				*rl_arg;
	char				*cmd_arg;
	int					type;
	struct s_lst_arg	*next;
	struct s_lst_arg	*prev;
}	t_lst_arg;

# define MAX_ARGS 1024

typedef struct s_cmd
{
	int				argc;
	char			*args[MAX_ARGS];
	char			*input_file;
	char			*output_file;
	int				append;
	int				here_doc;
	int				nb_ope;
	struct s_cmd	*next;

}				t_cmd;

typedef struct s_data
{
	char		**rl_tab;
	char		**glutto_tab;
	char		**re_token;
	char		**tab_env;
	char		*str;
	int			tab_len;
	int			pipefd1[2];
	int			pipefd2[2];
	int			pipe_nbr;
	void		*pid;
	int			stat_quo;
	int			pipe_quo;
	int			in_quo;
	t_lst_arg	*rl_lst;
	t_lst_arg	*cmd_arg;
	t_lst_arg	*ws_lst;
	t_cmd		*cmd;
}	t_data;

typedef struct s_pipe_ctx
{
	int	*current_pipe;
	int	prev_pipe_read;
}	t_pipe_ctx;

typedef struct s_echo_data
{
	int	i;
	int	j;
	int	n;
	int	n_def;
}	t_echo_data;

//? ***********SOURCES**********************************************?/
//**********MAIN_DIR*************************************************/
int			main(int argc, char **argv, char **envp);
void		free_cmd(t_cmd *cmd);
int			handle_readline(char *str, t_data **s_k, t_cmd *cmd);
int			handle_exit_command(char *str, t_data **suprem_knowledge);
int			handle_null_input(char *str, t_cmd *cmd, t_data **suprem_knowledge);
void		process_input_string(char **str, t_data **suprem_knowledge);
void		process_input_string_2(char *str, t_data **s_k, t_cmd *cmd);
void		handle_ending(t_data **s_k, int exit_code);
void		handle_str(char *str, t_data **s_k, t_cmd *cmd);
void		cleanup_data_tabs(t_data **s_k);
char		*trim_quottage(char *str, int i, int j);

//**********UTILS_DIR********************************************/
void		free_tab(char **tab);
void		str_error(char *str, char *cmd_args, char *msg);
int			find_closing_quote(char *str, char c);
int			is_operator(char c);
void		skip_whitespace(char **src);
t_cmd		*parse_cmd(char **token);
void		free_glutto_tab_elements(t_data **s_k);
void		free_glutto_tab_array(t_data **s_k);
void		cleanup_data_tabs(t_data **s_k);
int			quote_verif(char *str, t_data **s_k);
void		pipe_quota(char *str, t_data **s_k);
int			check_arguments(int argc, char **argv);

//**********PARSING_DIR*********************************************/
int			is_whitespace(char c);
void		handle_pipe(char **token, int *i, t_cmd **current);
void		handle_append_output(char **token, int *i, t_cmd *current);
void		arg_to_cmd(t_cmd *cmd, char *arg);
void		handle_output(char **token, int *i, t_cmd *current);
t_cmd		*new_cmd(void);
int			process_token(char **token, int i, t_cmd **current);
void		init_suprem_knowledge(t_data **s_k, char **envp);
void		free_data(t_data **s_k);
int			double_redir_start(char *str, int i);
int			double_redir_middle(char *str, int i);
int			single_redir_start(char *str, int i);
int			single_redir_middle(char *str, int i);
int			quotes_part2(char *str, int *i, int *quote, char c);
int			quotes(char *str, int *i, int *word);
int			redirections_part1(char *str, int i, int *inc);
int			redirections_part2(char *str, int i, int *inc);
int			redirections(char *str, int i, int *inc);
int			process_redir(char *str, int *i, int ret, int inc);
int			process_word(char *str, int *i, int *word);
int			count_letters(char *str);
void		double_redir_w(const char *str, int *i, int *word);
void		single_redir_no_space(const char *str, int *i, int *word);
void		single_redir_partial_space_1(const char *str, int *i, int *word);
void		single_redir_partial_space_2(const char *str, int *i, int *word);
void		quotes_part2_w(const char *str, int *i, int *quote, char c);
void		quotes_w(const char *str, int *i, int *word, int *quote);
void		redirections_w(const char *str, int *i, int *word);
void		process_word_w(const char *str, int *i, int *word, int *quote);
int			count_words(const char *str);
void		fill_suprem_knowledge(t_data **s_k, char *str);
void		copy_word(char *dest, char **src, int count_l);
void		fill_s_k_tab(t_data **s_k, char *str);
void		glt_copy_word(char *dest, char **src, int count_l, t_data **s_k);
void		fill_gluttony_tab(t_data **s_k, char *str);
void		fill_tabs(t_data **s_k, char *str);
int			handle_quotes_part2(char *str, int *i, int *quote, char c);
int			handle_quotes(char *str, int *i, int *word);
int			handle_double_redir(char *str, int i, int *inc);
int			handle_single_redir(char *str, int i, int *inc);
int			handle_redirections(char *str, int i, int *inc);
int			process_word_part2(char *str, int *i, int *word, int redir_pos);
int			glt_process_word(char *str, int *i, int *word, t_data **s_k);
void		skip_spaces(char *str, int *i);
int			glt_count_letters(char *str, t_data **s_k);
void		skip_spaces_w(const char *str, int *i);
void		handle_double_redir_w(const char *str, int *i, int *word);
void		handle_single_redir_no_space(const char *str, int *i, int *word);
void		handle_single_redir_partial_space_1(const char *str,
				int *i, int *word);
void		handle_single_redir_partial_space_2(const char *str,
				int *i, int *word);
void		handle_quotes_part2_w(const char *str, int *i, int *quote, char c);
void		handle_quotes_w(const char *str, int *i, int *word, int *quote);
void		handle_redirections_w(const char *str, int *i, int *word);
int			glt_count_words(const char *str);
void		handle_standard_token(t_data **s_k, char **str, int *i);
int			allocate_glutto_tab(t_data **s_k, char *str);
void		fill_tab_env(t_data **s_k, char **envp);
int			cmd_nt_fd(char *str);

//**********EXEC_DIRECTORY*****************************************/
int			init_pipefd(int *pipefd);
int			handle_exec(t_data *s_k, t_cmd *cmd, int i);
int			ft_exec_multipipe(t_data *s_k, t_cmd *cmd);
int			ft_exec_nopipe(t_data *s_k, t_cmd *cmd);
char		*get_way(char **env, char **rl_tab);
int			ft_exec_builtin(t_data *s_k, t_cmd *cmd);
int			ft_is_builtin(char *cmd);
int			ft_heredoc(char *safeword, t_cmd *cmd, t_data *s_k);
int			handle_redirection(t_cmd *cmd, t_data *s_k);
void		setup_pipe(int i, int pipe_nbr, int pipefd1[2], int pipefd2[2]);
void		safe_close(int fd);
void		free_and_exit_in_child_p(t_data *s_k, t_cmd *cmd, int ex_code);
void		ft_child_cleanup_and_exit(t_data *s_k);
void		ft_exec_builtin_child(t_data *s_k, t_cmd *cmd);
void		setup_middle_even_cmd(int pipefd1[2], int pipefd2[2]);
void		setup_middle_odd_cmd(int pipefd1[2], int pipefd2[2]);
void		setup_last_cmd(int i, int pipefd1[2], int pipefd2[2]);
int			handle_input_redirection(t_cmd *cmd, t_data *s_k, int fd);
int			handle_output_redirection(t_cmd *cmd, int fd);
void		exit_in_heredoc(char *tmp, int *pipefd, t_cmd *cmd, t_data *s_k);
void		handle_heredoc_input(int pipefd[2],
				char *safeword, t_cmd *cmd, t_data *s_k);
int			open_input(t_cmd *cmd, t_data *s_k);
void		to_execve(t_data *s_k, t_cmd *current_cmd, t_cmd *cmd);
int			end_of_multipipe(int *prev_pipe_read);

//**********SIGNALS_DIR**********************************************/
void		setup_signal(void);
void		signal_heredoc(int signal);

//**********BUILTIN_DIRECTORY**********************************************/
int			ft_echo(char **str);
void		init_echo_data(t_echo_data *data);
void		handle_escaped_dollar(char *str);
void		handle_special_chars(char *str);
void		handle_exit_code(void);
void		handle_quoted_variable(char *str);
int			ft_cd(char **args, char ***envp);
char		*ft_getenv(const char *name, char **envp);
char		*create_env_var(char *name, char *value);
int			update_existing_var(char ***envp, char *name,
				size_t name_len, char *new_var);
int			add_new_var(char ***envp, char *new_var);
int			ft_env(char **envp);
int			ft_export(char **args, char ***envp);
int			update_existing_var2(char ***envp, char *arg);
int			check_arg_export(char *str, int i);
int			check_arg_export_2(char *str, int i);
void		add_new_var2(char ***envp, char *arg);
int			ft_pwd(void);
int			ft_unset(char **args, char ***envp, int i, int j);
void		ft_exit(int err_value);
void		free_s_k(t_data **s_k);
void		free_glt(t_data **s_k);
int			check_exit_args(char *str);
int			validate_exit_argument(char *tmp);
int			validate_argument_char(char *tmp, int arg_nbr, int i);
int			handle_whitespace(char *tmp, int *i, int *arg_nbr);
int			skip_special_chars(char *tmp, int *i);
int			handle_argument_errors(char *tmp, int arg_nbr, char c);

#endif
