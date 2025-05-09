/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:22:04 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/09 11:48:38 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include "libft/libft.h"


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
