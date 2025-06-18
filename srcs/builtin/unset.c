/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:39 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/18 18:03:16 by qumiraud         ###   ########.fr       */
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

int	ft_suppr_var(char ***envp, int var_pos)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	i = 0;
	j = 0;
	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (1);
	while (i < count)
	{
		if (i != var_pos)
		{
			new_env[j] = (*envp)[i];
			j++;
		}
		else
			free((*envp)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*envp);
	(*envp) = new_env;
	return (0);
}

int	ft_unset(char **args, char ***envp)
{
	int		i;
	int		j;
	int		var_len;

	j = 0;
	i = 1;
	if (!args[1])
		return (0);
	if (!args[1][0])
	{
		str_error("bash: ", args[1], ": not a valid identifier");
		return (0);
	}
	while (args[i])
	{
		j = 0;
		while ((*envp)[j])
		{
			var_len = ft_varlen(args[i], '=');
			if (ft_strncmp((*envp)[j], args[i], var_len) == 0 &&
				args[i][var_len] == '\0' &&
					(*envp)[j][var_len] == '=')
			{
				ft_suppr_var(envp, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
