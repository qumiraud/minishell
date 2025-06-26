/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:24:25 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/26 08:21:47 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*input_with_space(char *str)
{
	char	*new_str;

	new_str = NULL;
	if (!str)
		return (NULL);
	new_str = ft_strjoin(" ", str);
	if (!new_str)
		return (NULL);
	free (str);
	str = NULL;
	return (new_str);
}

int	check_arguments(int argc, char **argv)
{
	if (argc > 1)
	{
		argv[0] = NULL;
		return (1);
	}
	return (0);
}

char	*trim_quottage(char *str, int i, int j)
{
	char	*dest;
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = ft_strdup(str);
	while (tmp[i++])
	{
		if (tmp[i] == '"' || tmp[i] == '\'')
			j++;
	}
	dest = malloc(sizeof(char) * ft_strlen(tmp) - j + 1);
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] != '\'' && tmp[i] != '"')
			dest[j++] = tmp[i];
		i++;
	}
	dest[j] = '\0';
	free(tmp);
	return (dest);
}

int	check_exit_args(char *str)
{
	int		i;
	int		arg_nbr;
	char	*tmp;

	i = 0;
	arg_nbr = 0;
	if (ft_strlen(str) <= 5)
		return (0);
	str += 5;
	tmp = trim_quottage(str, 0, 0);
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '"')
			i++;
		if (tmp[0] == '-' || tmp[0] == '+')
			i++;
		if (tmp[i] == '\0')
			break ;
		while (tmp[i] == ' ' || (tmp[i] >= 8 && tmp[i] <= 13))
		{
			if (tmp[i - 1] > ' ')
				arg_nbr ++;
			i++;
		}
		if (tmp[i] == '\'' || tmp[i] == '"')
			i++;
		if (arg_nbr > 0)
		{
			printf("bash: exit: too many arguments\n");
			g_status = 1;
			free (tmp);
			return (1);
		}
		if (tmp[i] < '0' || tmp[i] > '9')
		{
			printf("%c : tmp[i]\n", tmp[i]);
			printf("bash: exit: %s: numeric argument required\n", tmp);
			g_status = 1;
			free(tmp);
			return (2);
		}
		i++;
	}
	if (tmp)
		g_status = ft_atoi(tmp);
	free(tmp);
	return (g_status);
}

int	handle_exit_command(char *str, t_data **suprem_knowledge)
{
	int	exit_value;

	exit_value = 0;
	if (str && ft_strncmp(str, "exit", 4) == 0)
	{
		exit_value = check_exit_args(str);
		if (exit_value != 1)
		{
			free(str);
			handle_ending(suprem_knowledge, exit_value);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	handle_null_input(char *str, t_cmd *cmd, t_data **suprem_knowledge)
{
	if (!str)
	{
		printf("exit\n");
		free_cmd(cmd);
		handle_ending(suprem_knowledge, 0);
		return (1);
	}
	return (0);
}

void	process_input_string(char **str, t_data **suprem_knowledge)
{
	if (*str && (*str)[0] != 0)
	{
		*str = input_with_space(*str);
		(*suprem_knowledge)->str = *str;
	}
}
