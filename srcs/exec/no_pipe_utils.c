/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:11:29 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 10:16:19 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_input(t_cmd *cmd, t_data *s_k)
{
	int	fd;

	if (cmd->here_doc)
	{
		fd = ft_heredoc(cmd->input_file, cmd, s_k);
	}
	else
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror("Error");
			return (-1);
		}
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	ft_child_cleanup_and_exit(t_data *s_k)
{
	free_data(&s_k);
	free(s_k);
	ft_exit(0);
}

void	ft_exec_builtin_child(t_data *s_k, t_cmd *cmd)
{
	ft_exec_builtin(s_k, cmd);
	free_cmd(cmd);
	free_data(&s_k);
	free(s_k);
	ft_exit(0);
}
