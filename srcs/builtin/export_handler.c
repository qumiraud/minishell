/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:44:00 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/25 19:48:28 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_varlen(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i);
}

int	update_existing_var2(char ***envp, char *arg)
{
	int	var_len;
	int	i;

	var_len = ft_varlen(arg, '=');
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], arg, var_len) == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_arg_export(char *str, int i)
{
	if (str[0] == '=')
		return (printf("bash: export: ʻ=': not a valid identifier\n"));
	else if (str[0] == '\0')
		return (printf("bash: export: ʻ': not a valid identifier\n"));
	else if (str[0] == '%')
		return (printf("bash: export: ʻ%%': not a valid identifier\n"));
	else if (str[0] == '0')
		return (printf("bash: export: ʻ0': not a valid identifier\n"));
	else if (str[0] == '?')
		return (printf("bash: export: ʻ?': not a valid identifier\n"));
	else if (ft_isdigit(str[0]))
		return (printf("bash: export: ʻ%c': not a valid identifier\n", str[0]));
	else
	{
		while (str[i] && str[i] != '=')
		{
			if (!isalnum(str[i]) || str[i] == '+' || str[i] == '-')
			{
				printf("bash: export: `%s': not a valid identifier\n", str);
				return (2);
			}
			i++;
		}
	}
	return (0);
}

int	check_arg_export_2(char *str, int i)
{
	while (str[i] && str[i] != '=')
		i++;
	printf("i : %d\n\n", i);
	while (str[i])
	{
		i++;
		if (str[i] == '(')
			return (printf("bash: syntax error near unexpected token `('\n"));
		else if (str[i] == ')')
			return (printf("bash: syntax error near unexpected token `)'\n"));
		else if (str[i] == '&')
			return (printf("\'&\' doesn't valid in minishell\n"));
		else if (str[i] == '!')
			return (printf("bash: %s: event not found\n", str + i));
	}
	return (0);
}
