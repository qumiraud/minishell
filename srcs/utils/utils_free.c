/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:11:38 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/12 15:19:25 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_glutto_tab_elements(t_data **s_k)
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
	}
}
