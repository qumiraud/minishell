/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:45 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/17 16:16:29 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

int	init_pipefd(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

// int	ft_exec_nopipe(t_data *s_k, t_cmd *cmd)
// {
// 	pid_t	pid;
// 	int		fd_in;
// 	int		fd_out;
// 	char	*pathway ;


// 	fd_out = 0;
// 	fd_in = 0;
// 	if (ft_is_builtin(cmd->args[0]) && !cmd->input_file && !cmd->output_file)
// 	{
// 		ft_exec_builtin(s_k, cmd);
// 		return (0);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	else if (pid == 0)
// 	{
// 		if (cmd->input_file)
// 		{
// 			if (cmd->here_doc == 1)
// 			{
// 				fd_in = ft_heredoc(cmd->input_file);
// 				dup2(fd_in, STDIN_FILENO);
// 				close(fd_in);
// 			}
// 			else
// 			{
// 				fd_in = open(cmd->input_file, O_RDONLY);
// 				if (fd_in == -1)
// 				{
// 					perror("Error");
// 					exit(1);
// 				}
// 				dup2(fd_in, STDIN_FILENO);
// 				close(fd_in);
// 			}
// 		}
// 		if (cmd->output_file)
// 		{
// 			if (cmd->append == 0)
// 				fd_out = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			else
// 				fd_out = open(cmd->output_file, O_RDWR | O_CREAT | O_APPEND, 0644);
// 			if (fd_out == -1)
// 			return (1);
// 			dup2(fd_out, STDOUT_FILENO);
// 			close (fd_out);
// 		}
// 		if (ft_is_builtin(cmd->args[0]))
// 		{
// 			ft_exec_builtin(s_k, cmd);
// 			free_cmd(cmd);
// 		}
// 		else
// 		{
// 			pathway = get_way(s_k->tab_env, cmd->args);
// 			if (!pathway)
// 			{
// 				str_error("bash :", cmd->args[0], "command not found");
// 				free_data(&s_k);
// 				free_cmd(cmd);
// 				free(s_k);
// 				exit (127);
// 			}
// 			else if (execve(pathway, cmd->args, s_k->tab_env) == -1)
// 			{
// 				if (cmd->args[0][0] == '.' && cmd->args[0][1] == '\0')
// 					str_error("bash :", NULL, "filename argument required");
// 				else if ((cmd->args[0][0] == '>' || cmd->args[0][0] == '<') && (cmd->args[0][1] == '<' || cmd->args[0][1] == '>' || cmd->args[0][1] == '\0' || cmd->args[0][1] == ' '))
// 				{
// 					if ((cmd->args[0][2] == '>' || cmd->args[0][3] == '<'))
// 					{
// 						str_error("bash :", "syntax error near unexpected token `newline'", &cmd->args[0][3]);
// 						free (pathway);
// 						free_data(&s_k);
// 						free(s_k);
// 						free(cmd);
// 						exit (2);
// 					}
// 					str_error("bash :", NULL, "syntax error near unexpected token `newline'");
// 				}
// 				else
// 				{
// 					str_error("bash :", cmd->args[0], "command not found");
// 					int	i = 0;
// 					printf("args[0] : %s \npathway : %s\n", cmd->args[0], pathway);
// 					if (ft_strcmp(cmd->args[0], pathway) == 0)
// 						free(pathway);
// 					while (cmd->args[i])
// 					{
// 						free(cmd->args[i]);
// 						i++;
// 					}
// 					free(cmd->input_file);
// 				}
// 				if (cmd->output_file)
// 					free(cmd->output_file);
// 				free_data(&s_k);
// 				free(s_k);
// 				free(cmd);
// 				exit (127);
// 			}
// 		}
// 		free_data(&s_k);
// 		free(s_k);
// 		exit(0);
// 	}
// 	else
// 		wait (NULL);
// 	return (0);
// }

int	handle_exec(t_data *s_k, t_cmd *cmd)
{
	// g_sig = 0;
	// printf("passage par handle_exec\n");
	if (s_k->pipe_quo > 1)
		ft_exec_multipipe(s_k, cmd);
	else if (s_k->pipe_quo == 1)
		ft_exec_singlepipe(s_k, cmd);
	else if (s_k->pipe_quo == 0)
		ft_exec_nopipe(s_k, cmd);
	printf("g_status : %d\n", g_status);
	free_cmd(cmd);
	// printf ("g_sig : %d", g_sig);
	return (0);
}
