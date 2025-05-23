/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeten <yeten@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:53:00 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/22 10:55:02 by yeten            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	free_glt(t_data **s_k)
{
	int	i;
	int	len;

	i = 0;
	len = (*s_k)->tab_len;
	if ((*s_k)->glutto_tab)
	{
		while (i <= len)
		{
			free((*s_k)->glutto_tab[i]);
			(*s_k)->glutto_tab[i] = NULL;
			i++;
		}
		// (*s_k)->tab_len = 0;
		len = 0;
	}
	if ((*s_k)->glutto_tab)
	{
		free((*s_k)->glutto_tab);
		(*s_k)->glutto_tab = NULL;
	}
		// if ((*s_k)->tab_env)
	// 	free_tab((*s_k)->tab_env);
}



void	free_s_k(t_data **s_k)
{
	int	i;
	int	len;

	i = 0;
	len = (*s_k)->tab_len;
	if ((*s_k)->rl_tab)
	{
		while (i <= len)
		{
			free((*s_k)->rl_tab[i]);
			(*s_k)->rl_tab[i] = NULL;
			i++;
		}
		len = 0;
	}
	if ((*s_k)->rl_tab)
	{
		free((*s_k)->rl_tab);
		(*s_k)->rl_tab = NULL;
	}
	if ((*s_k)->tab_env)
	{
		free_tab((*s_k)->tab_env);
		(*s_k)->tab_env = NULL;
	}
}



void	free_data(t_data **s_k)
{
	free((*s_k)->str);
	free_s_k(s_k);
	free_glt(s_k);
}





void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
