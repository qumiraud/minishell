/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:36:49 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/24 13:43:22 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_quotes(char *str, int *i, char quote_type)
{
	if (str[*i] == quote_type && str[*i + 1] != '\0')
	{
		(*i)++;
		while (str[*i] && str[*i] != quote_type && str[*i + 1] != '\0')
			(*i)++;
	}
}

void	pipe_quota(char *str, t_data **s_k)
{
	int	i;
	int	str_len;
	int	pipe;

	i = 0;
	str_len = 0;
	pipe = 0;
	if (!str)
		return ;
	str_len = ft_strlen((const char *)str);
	while (i <= str_len)
	{
		skip_quotes(str, &i, '\'');
		skip_quotes(str, &i, '"');
		if (str[i] == '|')
			pipe++;
		i++;
	}
	(*s_k)->pipe_quo = pipe;
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
