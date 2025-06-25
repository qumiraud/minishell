/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:13:27 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/25 19:49:02 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	trim_space(char **str)
{
	char	*tmp;
	char	*dest;
	int		i;

	i = 0;
	dest = NULL;
	tmp = ft_strdup(*str);
	while ((*str)[i] != '=')
		i++;
	tmp[i + 1] = '\0';
	dest = ft_strdup(tmp);
	tmp[i + 1] = 'a';
	free(tmp);
	tmp = ft_strtrim((*str) + i + 1, " 	");
	free(*str);
	*str = ft_strjoin (dest, tmp);
	free(dest);
	free(tmp);
}

int	print_environment(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}

int	process_arguments(char **args, char ***envp)
{
	int	arg_nbr;
	int	result;

	arg_nbr = 1;
	result = 0;
	while (args[arg_nbr])
	{
		if (ft_strchr(args[arg_nbr], '='))
		{
			trim_space(&args[arg_nbr]);
			if (!update_existing_var2(envp, args[arg_nbr]))
				add_new_var(envp, args[arg_nbr]);
		}
		arg_nbr++;
	}
	return (result);
}

void	add_new_var(char ***envp, char *arg)
{
	int		env_len;
	int		i;
	char	**new_envp;

	env_len = 0;
	i = 0;
	while ((*envp)[env_len])
		env_len++;
	new_envp = malloc(sizeof(char *) * (env_len + 2));
	if (!new_envp)
		return ;
	while (i < env_len)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	new_envp[env_len] = ft_strdup(arg);
	new_envp[env_len + 1] = NULL;
	free(*envp);
	*envp = new_envp;
}

int	ft_export(char **args, char ***envp)
{
	if (!args[1])
		return (print_environment(*envp));
	if (check_arg_export(args[1], 0) != 0
		|| check_arg_export_2(args[1], 0) != 0)
		return (2);
	return (process_arguments(args, envp));
}
