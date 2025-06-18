/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:24:25 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/18 17:47:38 by qumiraud         ###   ########.fr       */
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

int	check_exit_args(char *str)
{
	int		i;
	int		arg_nbr;

	i = 0;
	arg_nbr = 0;
	str += 5;

	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		{
			if (str[i - 1] > ' ')
				arg_nbr ++;
			i++;
		}
		if (str[i] < '0' || str[i] > '9')
		{
			printf("%s: numeric argument required\n", str);
			g_status = 1;
			return (2);
		}
		if (arg_nbr > 0)
		{
			printf("bash: exit: too many arguments\n");
			g_status = 1;
			return (1);
		}
		i++;
	}
	g_status = ft_atoi(str);
	return (0);
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
