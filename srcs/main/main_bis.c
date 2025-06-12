/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:24:25 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/12 14:51:03 by pjurdana         ###   ########.fr       */
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

int	handle_exit_command(char *str, t_data **suprem_knowledge)
{
	if (ft_strcmp(str, "exit") == 1)
	{
		free(str);
		handle_ending(suprem_knowledge);
		return (1);
	}
	return (0);
}

int	handle_null_input(char *str, t_cmd *cmd, t_data **suprem_knowledge)
{
	if (!str)
	{
		printf("exit\n");
		free_cmd(cmd);
		handle_ending(suprem_knowledge);
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
