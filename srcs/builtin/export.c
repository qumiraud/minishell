/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:13:27 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/24 14:45:25 by qumiraud         ###   ########.fr       */
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
				return(printf("bash: export: `%s': not a valid identifier\n", str));
			i++;
		}
	}
	return (0);
}

int	check_arg_export_2(char *str, int i)
{
	while (str[i] && str[i] != '=')
		i++;
	while (str[++i])
	{
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

void	trim_space(char **str)
{
	char	*tmp;
	char	*dest = NULL;
	int		i;

	i = 0;
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
	if (check_arg_export(args[1], 0) != 0 || check_arg_export_2(args[1], 0) != 0)
		return (0);
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
		trim_space(&args[arg_nbr]);
		// printf("args[%d] : \'%s\'\n", arg_nbr, args[1]);
		// tmp = ft_strtrim(args[arg_nbr] + var_len + 1, " ");
		// printf("tmp : \'%s\'\n", tmp);

		while ((*envp)[i])
		{
			if (ft_strncmp((*envp)[i], args[arg_nbr], var_len) == 0 /*&& (*envp)[i][var_len] == '='*/)
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
