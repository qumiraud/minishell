/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:22:04 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/26 08:22:36 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_setenv(char *name, char *value, char ***envp)
{
	char	*new_var;
	size_t	name_len;

	if (!name || !envp || !*envp)
		return (1);
	new_var = create_env_var(name, value);
	if (!new_var)
		return (1);
	name_len = ft_strlen(name);
	if (update_existing_var(envp, name, name_len, new_var))
		return (0);
	return (add_new_var(envp, new_var));
}

static int	validate_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] && count <= 2)
		count++;
	if (count > 2)
	{
		printf("bash: cd: too many arguments\n");
		g_status = 1;
		return (1);
	}
	return (0);
}

static char	*get_target_path(char **args, char **envp, int *need_free)
{
	char	*home;

	if (!args[1])
	{
		home = ft_getenv("HOME", envp);
		*need_free = (home && home[0] != '\0');
		return (home);
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		*need_free = 1;
		return (ft_getenv("OLDPWD", envp));
	}
	*need_free = 0;
	return (args[1]);
}

static int	update_pwd_vars(char ***envp, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (1);
	ft_setenv("PWD", newpwd, envp);
	ft_setenv("OLDPWD", oldpwd, envp);
	free(newpwd);
	return (0);
}

int	ft_cd(char **args, char ***envp)
{
	char	*oldpwd;
	int		need_free;
	char	*target;

	if (validate_args(args))
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	need_free = 0;
	target = get_target_path(args, *envp, &need_free);
	if (!target || chdir(target) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", target);
		free(oldpwd);
		if (need_free || target[0] == '\0')
			free(target);
		g_status = 1;
		return (1);
	}
	if (need_free || target[0] == '\0')
		free(target);
	update_pwd_vars(envp, oldpwd);
	free(oldpwd);
	return (0);
}
