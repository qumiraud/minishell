/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathway.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:41:48 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/18 13:02:35 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path_in_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (&env[i][5]);
		i++;
	}
	return (NULL);
}

char	*search_executable(char **pathtab, char *cmd)
{
	char	*tmp;
	char	*absolut_path;
	int		j;

	j = 0;
	while (pathtab[j])
	{
		tmp = ft_strjoin(pathtab[j], "/");
		absolut_path = ft_strjoin(tmp, cmd);
		if (access(absolut_path, X_OK) == 0)
		{
			free(tmp);
			free_tab(pathtab);
			return (absolut_path);
		}
		free(tmp);
		free(absolut_path);
		j++;
	}
	return (NULL);
}

char	*get_way(char **env, char **rl_tab)
{
	char	**pathtab;
	char	*absolut_path;
	char	*path_value;

	if (!rl_tab[0] || *rl_tab[0] == 0)
		return (NULL);
	path_value = find_path_in_env(env);
	if (!path_value)
		return (rl_tab[0]);
	pathtab = ft_split(path_value, ':');
	if (!pathtab)
		return (rl_tab[0]);
	absolut_path = search_executable(pathtab, rl_tab[0]);
	if (absolut_path)
		return (absolut_path);
	free_tab(pathtab);
	return (rl_tab[0]);
}
