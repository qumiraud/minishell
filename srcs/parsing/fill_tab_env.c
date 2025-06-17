/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:41:43 by quentin           #+#    #+#             */
/*   Updated: 2025/06/17 15:17:20 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_tab_env(t_data **s_k, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	(*s_k)->tab_env = malloc(sizeof(char *) * (i + 1));
	if (!(*s_k)->tab_env)
		return ;
	i = 0;
	while (envp[i])
	{
		j = 0;
		(*s_k)->tab_env[i] = malloc(sizeof(char) * (ft_strlen(envp[i])) + 1);
		if (!(*s_k)->tab_env[i])
			return ;
		while (envp[i][j])
		{
			(*s_k)->tab_env[i][j] = envp[i][j];
			j++;
		}
		(*s_k)->tab_env[i][j] = '\0';
		i++;
	}
	(*s_k)->tab_env[i] = NULL;
}
