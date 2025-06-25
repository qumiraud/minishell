/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:22:04 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/25 19:28:00 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*ft_getenv(const char *name, char **envp)
// {
// 	char	*env_value;
// 	int		i;
// 	size_t	n_len;

// 	env_value = NULL;
// 	n_len = ft_strlen(name);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], name, n_len) == 0
// 			&& envp[i][n_len] == '=')
// 		{
// 			env_value = ft_strdup(envp[i] + n_len + 1);
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (env_value);
// }

// static char	*create_env_var(char *name, char *value)
// {
// 	char	*tmp;
// 	char	*new_var;

// 	tmp = ft_strjoin(name, "=");
// 	if (!tmp)
// 		return (NULL);
// 	new_var = ft_strjoin(tmp, value);
// 	free(tmp);
// 	return (new_var);
// }

// static int	update_existing_var(char ***envp, char *name,
// 							size_t name_len, char *new_var)
// {
// 	int	i;

// 	i = 0;
// 	while ((*envp)[i])
// 	{
// 		if (ft_strncmp((*envp)[i], name, name_len) == 0
// 			&& (*envp)[i][name_len] == '=')
// 		{
// 			free((*envp)[i]);
// 			(*envp)[i] = new_var;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// static int	add_new_var(char ***envp, char *new_var)
// {
// 	int		count;
// 	char	**new_env;
// 	int		i;

// 	i = 0;
// 	count = 0;
// 	while ((*envp)[count])
// 		count++;
// 	new_env = malloc(sizeof(char *) * (count + 2));
// 	if (!new_env)
// 	{
// 		free(new_var);
// 		return (1);
// 	}
// 	while (i < count)
// 	{
// 		new_env[i] = (*envp)[i];
// 		i++;
// 	}
// 	new_env[count] = new_var;
// 	new_env[count + 1] = NULL;
// 	free(*envp);
// 	*envp = new_env;
// 	return (0);
// }

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
// int	ft_setenv(char *var_name, char *pwd, char ***envp)
// {
// 	int		i;
// 	char	*new_var;
// 	char	*tmp;
// 	size_t	name_len;
// 	int		env_len;
// 	char	**new_env;

// 	name_len = ft_strlen(var_name);
// 	i = 0;
// 	tmp = ft_strjoin(var_name, "=");
// 	if (!tmp)
// 		return (1);
// 	new_var = ft_strjoin(tmp, pwd);
// 	free(tmp);
// 	while ((*envp)[i])
// 	{
// 		if (ft_strncmp((*envp)[i], var_name, name_len) == 0
			// && (*envp)[i][name_len] == '=')
// 		{
// 			free((*envp)[i]);
// 			(*envp)[i] = new_var;
// 			return (0);
// 		}
// 		i++;
// 	}
// 	env_len = 0;
// 	while ((*envp)[env_len])
// 		env_len++;
// 	new_env = malloc(sizeof(char *) * (env_len + 2));
// 	if (!new_env)
// 	{
// 		free(new_var);
// 		return (1);
// 	}
// 	i = 0;
// 	while (i < env_len)
// 	{
// 		new_env[i] = (*envp)[i];
// 		i++;
// 	}
// 	new_env[env_len] = new_var;
// 	new_env[env_len + 1] = NULL;
// 	free(*envp);
// 	*envp = new_env;
// 	return (0);
// }

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

// int	ft_cd(char **args, char ***envp)
// {
// 	char	*oldpwd;
// 	char	*newpwd;
// 	char	*newcurrentpwd;
// 	int		needfree;
// 	int		i;

// 	i = 0;
// 	needfree = 1;
// 	oldpwd = getcwd(NULL, 0);
// 	newpwd = NULL;
// 	newcurrentpwd = NULL;
// 	while (args[i] && i <= 2)
// 	{
// 		if (i == 2)
// 		{
// 			printf("bash: cd: too many arguments\n");
// 			free(oldpwd);
// 			g_status = 1;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	if (!args[1])
// 	{
// 		newpwd = ft_getenv("HOME", *envp);
// 		if (!newpwd || newpwd[0] == 0)
// 		{
// 			free(oldpwd);
// 			free(newpwd);
// 			g_status = 1;
// 			return (1);
// 		}
// 	}
// 	else if (ft_strncmp(args[1], "-", 1) == 0)
// 		newpwd = ft_getenv("OLDPWD", *envp);
// 	else
// 	{
// 		newpwd = args[1];
// 		needfree = 0;
// 	}
// 	if (!newpwd || chdir(newpwd) != 0)
// 	{
// 		printf("bash: cd: %s: No such file or directory\n", newpwd);
// 		free(oldpwd);
// 		// free(newpwd);
// 		g_status = 1;
// 		return (1);
// 	}
// 	if (needfree == 1)
// 		free(newpwd);
// 	ft_setenv("OLDPWD", oldpwd, envp);
// 	free(oldpwd);
// 	// free(newpwd);
// 	newcurrentpwd = getcwd(NULL, 0);
// 	if (newcurrentpwd)
// 	{
// 		ft_setenv("PWD", newcurrentpwd, envp);
// 		free(newcurrentpwd);
// 	}
// 	return (0);
// }

// int	main(int argc, char **argv, char **env)
// {
// 	if (argc < 1)
// 	{
// 		argv[1] = NULL;
// 		return (1);
// 	}
// 	char	**my_env;
// 	char	*val;
// 	char	*args1[] = {"cd", NULL};
// 	char	*args2[] = {"cd", "..", NULL};
// 	char	*args3[] = {"cd", "-", NULL};

// 	// Clone de env pour test modifiable
// 	int count = 0;
// 	while (env[count])
// 		count++;
// 	my_env = malloc(sizeof(char *) * (count + 1));
// 	for (int i = 0; i < count; i++)
// 		my_env[i] = ft_strdup(env[i]);
// 	my_env[count] = NULL;

// 	printf("=== TEST getenv ===\n");
// 	val = ft_getenv("PATH", my_env);
// 	if (val)
// 		printf("PATH = %s\n", val);
// 	else
// 		printf("PATH not found\n");
// 	free(val);

// 	printf("\n=== TEST setenv ===\n");
// 	ft_setenv("MYTEST", "/home/user/test", &my_env);
// 	val = ft_getenv("MYTEST", my_env);
// 	printf("MYTEST = %s\n", val);
// 	free(val);

// 	printf("\n=== TEST cd (to HOME) ===\n");
// 	ft_cd(args1, &my_env);
// 	val = ft_getenv("PWD", my_env);
// 	printf("PWD after cd: %s\n", val);
// 	free(val);

// 	printf("\n=== TEST cd .. ===\n");
// 	ft_cd(args2, &my_env);
// 	val = ft_getenv("PWD", my_env);
// 	printf("PWD after cd ..: %s\n", val);
// 	free(val);

// 	printf("\n=== TEST cd - ===\n");
// 	ft_cd(args3, &my_env);
// 	val = ft_getenv("PWD", my_env);
// 	printf("PWD after cd -: %s\n", val);
// 	free(val);

// 	// Libération de my_env
// 	for (int i = 0; my_env[i]; i++)
// 		free(my_env[i]);
// 	free(my_env);
// 	return 0;
// }
