/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:34:30 by qumiraud          #+#    #+#             */
/*   Updated: 2025/04/22 15:04:27 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo_cmp(const char *str, char *cmp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[j])
	{
		if (str[j] == cmp[i])
		{
			i++;
			j++;
		}
		else if(str[j] == 39 || str[j] == 34)
			j++;
		else if (i == 3)
		{
			break;
		}
		else
			exit(127);
	}
	exit (0);
}

void	ft_echo(char **tab)
{
// 	int	i; //TODO :de la merde tyout est a recommence, le seul truc conservable c'est le nom du fichier xD
// 	pid_t	pid;

// 	i = 0;
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("PID error\n");
// 		return ;
// 	}

// 		if (ft_echo_cmp(tab[0], "echo"))
}
