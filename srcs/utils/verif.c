/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:36:49 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/14 12:10:41 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_quota(char *str, t_data **s_k)
{
	static int	i = 0;
	static int	pipe = 0;

	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] != '\0')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '"' && str[i + 1] != '\0')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
		}
		if (str[i] == '|')
			pipe++;
		if (str[i] == '\0')
			break;
		i++;
	}
	(*s_k)->pipe_quo = pipe;
	return (0);
}

int	quote_verif(char *str, t_data **s_k)
{
	int	i;
	int	quote;
	int	d_quote;

	i = 0;
	quote = 0;
	d_quote = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '"')
			d_quote++;
		if (str[i] == '\'')
			quote++;
		i++;
	}
	(*s_k)->stat_quo = d_quote + quote;
	if (quote % 2 != 0)
		return (printf("missing quote\n"));
	if (d_quote % 2 != 0)
		return (printf("missing double quote\n"));
	return (0);
}
