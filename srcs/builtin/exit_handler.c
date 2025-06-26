/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:23:22 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 11:23:59 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_special_chars(char *tmp, int *i)
{
	if (tmp[*i] == '\'' || tmp[*i] == '"')
	{
		(*i)++;
		return (1);
	}
	if ((tmp[*i] == '-' || tmp[*i] == '+') && *i == 0)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_whitespace(char *tmp, int *i, int *arg_nbr)
{
	if (tmp[*i] == ' ' || (tmp[*i] >= 8 && tmp[*i] <= 13))
	{
		if (*i > 0 && tmp[*i - 1] > ' ')
			(*arg_nbr)++;
		(*i)++;
		return (1);
	}
	return (0);
}

int	validate_argument_char(char *tmp, int arg_nbr, int i)
{
	int	error;

	error = handle_argument_errors(tmp, arg_nbr, tmp[i]);
	if (error)
		return (error);
	return (0);
}

int	validate_exit_argument(char *tmp)
{
	int	i;
	int	arg_nbr;
	int	result;

	i = 0;
	arg_nbr = 0;
	if (!tmp)
		return (0);
	while (tmp[i])
	{
		if (skip_special_chars(tmp, &i))
			continue ;
		if (handle_whitespace(tmp, &i, &arg_nbr))
			continue ;
		result = validate_argument_char(tmp, arg_nbr, i);
		if (result)
			return (result);
		i++;
	}
	return (0);
}
