/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:07:52 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 13:52:48 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	set_pipe_and_fork(t_cmd *current_cmd, int *current_pipe)
{
	pid_t	pid;

	if (current_cmd->next)
	{
		if (pipe(current_pipe) == -1)
		{
			perror("pipe");
			return (1);
		}
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

void	in_or_out_redir(t_cmd *curr_cmd, int *curr_pipe, int p_p_r, int in_out)
{
	if (in_out == 1)
	{
		if (p_p_r != -1)
		{
			if (dup2(p_p_r, STDIN_FILENO) == -1)
			{
				perror("dup2 input");
				exit(1);
			}
			close(p_p_r);
		}
	}
	else if (in_out == 2)
	{
		if (curr_cmd->next)
		{
			if (dup2(curr_pipe[1], STDOUT_FILENO) == -1)
			{
				perror("dup2 output");
				exit(1);
			}
			close(curr_pipe[1]);
			close(curr_pipe[0]);
		}
	}
}

void	parent_proc(t_cmd *current_cmd, int *prev_pipe_read, int *current_pipe)
{
	if (*prev_pipe_read != -1)
		close (*prev_pipe_read);
	if (current_cmd->next)
	{
		close (current_pipe[1]);
		*prev_pipe_read = current_pipe[0];
	}
}

static void	handle_child_process(t_data *s_k, t_cmd *cmd,
		t_cmd *current_cmd, t_pipe_ctx *pipe_ctx)
{
	in_or_out_redir(current_cmd, pipe_ctx->current_pipe,
		pipe_ctx->prev_pipe_read, 1);
	in_or_out_redir(current_cmd, pipe_ctx->current_pipe,
		pipe_ctx->prev_pipe_read, 2);
	if (current_cmd->input_file || current_cmd->output_file)
		handle_redirection(current_cmd, s_k);
	if (ft_is_builtin(current_cmd->args[0]))
	{
		ft_exec_builtin(s_k, current_cmd);
		free_and_exit_in_child_p(s_k, cmd, 1);
	}
	else
		to_execve(s_k, current_cmd, cmd);
}

int	ft_exec_multipipe(t_data *s_k, t_cmd *cmd)
{
	pid_t		pid;
	int			prev_pipe_read;
	int			current_pipe[2];
	t_cmd		*current_cmd;
	t_pipe_ctx	pipe_ctx;

	prev_pipe_read = -1;
	current_cmd = cmd;
	while (current_cmd)
	{
		pid = set_pipe_and_fork(current_cmd, current_pipe);
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			pipe_ctx.current_pipe = current_pipe;
			pipe_ctx.prev_pipe_read = prev_pipe_read;
			handle_child_process(s_k, cmd, current_cmd, &pipe_ctx);
		}
		parent_proc(current_cmd, &prev_pipe_read, current_pipe);
		current_cmd = current_cmd->next;
	}
	g_status = end_of_multipipe(&prev_pipe_read);
	return (0);
}
