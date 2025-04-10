/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:41:43 by quentin           #+#    #+#             */
/*   Updated: 2025/04/10 14:41:38 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_tab_env(t_data **s_k, char **envp)
{
	int	i;
	int	j;
	
	i = 0;
	printf("coucou\n");
	while (envp[i])
		i++;
	printf("i : %d\n", i);
	(*s_k)->tab_env = malloc(sizeof(char *) * (i + 1));
	if (!(*s_k)->tab_env)
	return ;
	i = 0;
	while (envp[i])
	{
		j = 0;
		(*s_k)->tab_env[i] = malloc(sizeof(char) * (ft_strlen(envp[i])));
		if ((*s_k)->tab_env[i])
		{
			/******freeeeeeeeee*******/
			return ; //free a prevoir//
		}
		while (envp[i][j])
		{
			(*s_k)->tab_env[i][j] = envp[i][j];
			j++;
		}
		(*s_k)->tab_env[i][j] = '\0';
		printf("intheboucle env : %s\n", (*s_k)->tab_env[i]);
		i++;
	}
	(*s_k)->tab_env[i] = NULL;
	// /////********test */
	// i = 0;
	// while ((*s_k)->tab_env[i])
	// {
	// 	free((*s_k)->tab_env[i]);
	// 	i++;
	// }
	// free((*s_k)->tab_env);
	// ///***********test */
}
