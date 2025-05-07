/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:22:04 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/07 16:50:11 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(const char *name, char **envp)
{
	char	*env_value;
	int		i;
	size_t	name_len;

	env_value = NULL;
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
		{
			env_value = ft_strdup(envp[i] + name_len + 1);
			break;
		}
		i++;
	}
	return (env_value);
}

int	ft_setenv(char *var_name, char *pwd, char ***envp)
{
	int		i;
	char	*new_var;
	char	*tmp;
	size_t	name_len;
	int		env_len;
	char	**new_env;

	name_len = ft_strlen(var_name);
	i = 0;
	tmp = ft_strjoin(var_name, "=");
	if (!tmp)
		return (1);
	new_var = ft_strjoin(tmp, pwd);
	free(tmp);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var_name, name_len) == 0 && (*envp)[i][name_len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_var;
			return (0);
		}
		i++;
	}
	env_len = 0;
	while ((*envp)[env_len])
		env_len++;
	new_env = malloc(sizeof(char *) * (env_len + 2));
	if (!new_env)
	{
		free(new_var);
		return (1);
	}
	i = 0;
	while (i < env_len)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[env_len] = new_var;
	new_env[env_len + 1] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}


int	ft_cd(char **args, char ***envp)
{
	char	*oldpwd;
	char	*newpwd;
	char	*newcurrentpwd;
	int		needfree;

	needfree = 1;
	oldpwd = getcwd(NULL, 0);
	newpwd = NULL;
	newcurrentpwd = NULL;
	if (!args[1])
		newpwd = ft_getenv("HOME", *envp);
	else if (ft_strncmp(args[1], "-", 1) == 0)
		newpwd = ft_getenv("OLDPWD", *envp);
	else
	{
		newpwd = args[1];
		needfree = 0;
	}
	if (!newpwd || chdir(newpwd) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	if (needfree == 1)
		free(newpwd);
	ft_setenv("OLDPWD", oldpwd, envp);
	free(oldpwd);
	newcurrentpwd = getcwd(NULL, 0);
	if (newcurrentpwd)
	{
		ft_setenv("PWD", newcurrentpwd, envp);
		free(newcurrentpwd);
	}
	return (0);
}
