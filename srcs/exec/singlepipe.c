/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlepipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:04:47 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/23 12:04:42 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command_in_child(t_data *s_k, t_cmd *cmd, t_cmd *original_cmd)
{
	char	*pathway;

	if ((cmd->output_file || cmd->input_file) && handle_redirection(cmd, s_k) == 1)
		free_and_exit_in_child_p(s_k, original_cmd, 1);
	if (ft_is_builtin(cmd->args[0]))
	{
		ft_exec_builtin(s_k, cmd);
		free_and_exit_in_child_p(s_k, original_cmd, 0);
	}
	else
	{
		pathway = get_way(s_k->tab_env, cmd->args);
		if (!pathway)
		{
			str_error("bash :", cmd->args[0], "command not found");
			free_and_exit_in_child_p(s_k, original_cmd, 127);
		}
		if (execve(pathway, cmd->args, s_k->tab_env) == -1)
		{
			str_error("bash :", cmd->args[0], "command not found");
			free_and_exit_in_child_p(s_k, original_cmd, 1);
		}
	}
}

pid_t	handle_first_child(t_data *s_k, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGPIPE, SIG_DFL);
		close(s_k->pipefd1[0]);
		dup2(s_k->pipefd1[1], STDOUT_FILENO);
		close(s_k->pipefd1[1]);
		execute_command_in_child(s_k, cmd, cmd);
	}
	return (pid);
}

pid_t	handle_second_child(t_data *s_k, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(s_k->pipefd1[1]);
		dup2(s_k->pipefd1[0], STDIN_FILENO);
		close(s_k->pipefd1[0]);
		execute_command_in_child(s_k, cmd->next, cmd);
	}
	return (pid);
}

void	wait_for_children(pid_t pid1, pid_t pid2)
{
	int		status;
	int		childreturn;

	childreturn = waitpid(pid1, &status, 0);
	// printf("pid1 : %d\n\n\n", childreturn);
	childreturn = waitpid(pid2, &status, 0);
	// printf("pid2 : %d\n\n\n", childreturn);
}

int	ft_exec_singlepipe(t_data *s_k, t_cmd *cmd)
{
	pid_t	pid1;
	pid_t	pid2;

	if (init_pipefd(s_k->pipefd1) != 0)
		return (1);
	if (!cmd->next)
		return (1);
	pid1 = handle_first_child(s_k, cmd);
	if (pid1 == -1)
		return (1);
	pid2 = handle_second_child(s_k, cmd);
	if (pid2 == -1)
		return (1);
	close(s_k->pipefd1[0]);
	close(s_k->pipefd1[1]);
	wait_for_children(pid1, pid2);
	return (0);
}

// int	ft_exec_singlepipe(t_data *s_k, t_cmd *cmd)
// {
// 	pid_t	pid1, pid2;
// 	int		status;
// 	t_cmd	*tmp;

// 	tmp = cmd;
// 	if (init_pipefd(s_k->pipefd1) != 0)
// 		return (1);

// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		signal(SIGPIPE, SIG_DFL);
// 		close(s_k->pipefd1[0]);
// 		dup2(s_k->pipefd1[1], STDOUT_FILENO);
// 		close(s_k->pipefd1[1]);

// 		if (cmd->output_file || cmd->input_file)
// 			handle_redirection(cmd);  // À écrire → open + dup2
// 		if (ft_is_builtin(cmd->args[0]))
// 		{
// 			ft_exec_builtin(s_k, cmd);
// 			free_cmd(cmd);
// 			free_data(&s_k);
// 			free(s_k);
// 			exit(1);
// 		}
// 		else
// 		{
// 			char *pathway = get_way(s_k->tab_env, cmd->args);
// 			if (!pathway)
// 			{
// 				str_error("bash :", cmd->args[0], "command not found");
// 				free_cmd(cmd);
// 				free_data(&s_k);
// 				free(s_k);
// 				exit(127);
// 			}
// 			if (execve(pathway, cmd->args, s_k->tab_env) == -1)
// 			{
// 				str_error("bash :", cmd->args[0], "command not found");
// 				free_cmd(cmd);
// 				free_data(&s_k);
// 				free(s_k);
// 			}
// 			exit(1);
// 		}
// 	}
// 	if (!tmp->next)
// 		return (1);
// 	tmp = tmp->next;
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		close(s_k->pipefd1[1]);
// 		dup2(s_k->pipefd1[0], STDIN_FILENO);
// 		close(s_k->pipefd1[0]);

// 		if (tmp->output_file || tmp->input_file)
// 		{
// 			if (handle_redirection(tmp) == 1)
// 			{
// 				free_cmd(cmd);
// 				free_data(&s_k);
// 				free(s_k);
// 				exit(1);
// 			}
// 		}// idem
// 		if (ft_is_builtin(tmp->args[0]))
// 		{
// 			ft_exec_builtin(s_k, tmp);
// 			free_cmd(cmd);
// 			free_data(&s_k);
// 			free(s_k);
// 			exit(0);
// 		}
// 		else
// 		{
// 			char *pathway = get_way(s_k->tab_env, tmp->args);
// 			if (!pathway)
// 			{
// 				str_error("bash :", tmp->args[0], "command not found");
// 				free_cmd(cmd);
// 				free_data(&s_k);
// 				free(s_k);
// 				exit(127);
// 			}
// 			if (execve(pathway, tmp->args, s_k->tab_env) == -1)
// 			{
// 				str_error("bash :", tmp->args[0], "command not found");
// 				free_cmd(cmd);
// 				free_data(&s_k);
// 				free(s_k);
// 			}
// 			exit(1);
// 		}
// 	}
// 	close(s_k->pipefd1[0]);
// 	close(s_k->pipefd1[1]);
// 	int childreturn = waitpid(pid1, &status, 0);
// 	printf("pid1 : %d\n\n\n",childreturn);
// 	int childreturn2 = waitpid(pid2, &status, 0);
// 	printf("pid2 : %d\n\n\n", childreturn2);
// 	return (0);
// }
