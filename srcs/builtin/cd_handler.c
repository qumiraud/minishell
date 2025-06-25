/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:04:19 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/25 19:12:10 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(const char *name, char **envp)
{
	char	*env_value;
	int		i;
	size_t	n_len;

	env_value = NULL;
	n_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, n_len) == 0
			&& envp[i][n_len] == '=')
		{
			env_value = ft_strdup(envp[i] + n_len + 1);
			break ;
		}
		i++;
	}
	return (env_value);
}

char	*create_env_var(char *name, char *value)
{
	char	*tmp;
	char	*new_var;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	return (new_var);
}

int	update_existing_var(char ***envp, char *name,
							size_t name_len, char *new_var)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, name_len) == 0
			&& (*envp)[i][name_len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_new_var(char ***envp, char *new_var)
{
	int		count;
	char	**new_env;
	int		i;

	i = 0;
	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(new_var);
		return (1);
	}
	while (i < count)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}
