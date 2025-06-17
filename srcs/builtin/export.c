/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:13:27 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/17 15:29:23 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include "libft/libft.h"

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

int	ft_export(char **args, char ***envp)
{
	int		i;
	int		var_len;
	char	**new_envp;
	int		env_len;
	int		arg_nbr;
	int	found;

	arg_nbr = 1;
	i = 0;
	if (!args[1])
	{
		while ((*envp)[i])
		{
			printf("%s\n", (*envp)[i]);
			i++;
		}
		return (0);
	}
	while (args[arg_nbr])
	{
		i = 0;
		found = 0;
		if (!ft_strchr(args[arg_nbr], '='))
		{
			arg_nbr++;
			continue;
		}
		var_len = ft_varlen(args[arg_nbr], '=');
		while ((*envp)[i])
		{
			if (ft_strncmp((*envp)[i], args[arg_nbr], var_len) == 0 && (*envp)[i][var_len] == '=')
			{
				free((*envp)[i]);
				(*envp)[i] = ft_strdup(args[arg_nbr]);
				found = 1;
				break;
			}
			i++;
		}
		if (!found)
		{
			i = 0;
			env_len = 0;
			while ((*envp)[env_len])
				env_len++;
			new_envp = malloc(sizeof(char *) * (env_len + 2));
			if (!new_envp)
				return (1);
			while (i < env_len)
			{
				new_envp[i] = (*envp)[i];
				i++;
			}
			new_envp[env_len] = ft_strdup(args[arg_nbr]);
			new_envp[env_len + 1] = NULL;
			free(*envp);
			(*envp) = new_envp;
		}
		arg_nbr++;
	}
	return (0);
}
