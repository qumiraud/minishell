/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:01:56 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 11:27:15 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(int err_value)
{
	g_status = err_value;
	exit (g_status % 255);
}

static char	*clean_exit_argument(char *str)
{
	if (ft_strlen(str) <= 5)
		return (NULL);
	return (trim_quottage(str + 5, 0, 0));
}

int	handle_argument_errors(char *tmp, int arg_nbr, char c)
{
	if (arg_nbr > 0)
	{
		printf("bash: exit: too many arguments\n");
		g_status = 1;
		return (1);
	}
	if (c && (c < '0' || c > '9'))
	{
		printf("bash: exit: %s: numeric argument required\n", tmp);
		g_status = 1;
		return (2);
	}
	return (0);
}

// int	skip_special_chars(char *tmp, int *i)
// {
// 	if (tmp[*i] == '\'' || tmp[*i] == '"')
// 	{
// 		(*i)++;
// 		return (1);
// 	}
// 	if ((tmp[*i] == '-' || tmp[*i] == '+') && *i == 0)
// 	{
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

// int	handle_whitespace(char *tmp, int *i, int *arg_nbr)
// {
// 	if (tmp[*i] == ' ' || (tmp[*i] >= 8 && tmp[*i] <= 13))
// 	{
// 		if (*i > 0 && tmp[*i - 1] > ' ')
// 			(*arg_nbr)++;
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

// int	validate_argument_char(char *tmp, int arg_nbr, int i)
// {
// 	int	error;

// 	error = handle_argument_errors(tmp, arg_nbr, tmp[i]);
// 	if (error)
// 		return (error);
// 	return (0);
// }

// int	validate_exit_argument(char *tmp)
// {
// 	int	i;
// 	int	arg_nbr;
// 	int	result;

// 	i = 0;
// 	arg_nbr = 0;
// 	if (!tmp)
// 		return (0);
// 	while (tmp[i])
// 	{
// 		if (skip_special_chars(tmp, &i))
// 			continue ;
// 		if (handle_whitespace(tmp, &i, &arg_nbr))
// 			continue ;
// 		result = validate_argument_char(tmp, arg_nbr, i);
// 		if (result)
// 			return (result);
// 		i++;
// 	}
// 	return (0);
// }

int	check_exit_args(char *str)
{
	char	*tmp;
	int		result;

	tmp = clean_exit_argument(str);
	if (!tmp)
		return (0);
	result = validate_exit_argument(tmp);
	if (result)
	{
		free(tmp);
		return (result);
	}
	g_status = ft_atoi(tmp);
	free(tmp);
	return (g_status);
}
