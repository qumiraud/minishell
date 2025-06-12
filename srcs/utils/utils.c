/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:53:00 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/12 15:33:24 by pjurdana         ###   ########.fr       */
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
		len = 0;
	}
	if ((*s_k)->glutto_tab)
	{
		free((*s_k)->glutto_tab);
		(*s_k)->glutto_tab = NULL;
	}
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

int	find_closing_quote(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
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
