/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:45 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/16 13:52:53 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void init_pipefd(int *pipefd)
{
	pipefd = malloc(2 * sizeof(int));
	if (pipe(pipefd) == -1)
	{
		free(pipefd);
		return;
	}
	return;
}


int	ft_exec(t_data *s_k)
{
	int	*pipefd;

	init_pipefd(pipefd);
	if (pid == -1)
		return(-1);
	else if (pid == 0)
	{

	}
}