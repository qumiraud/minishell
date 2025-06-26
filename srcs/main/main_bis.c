/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:24:25 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/26 11:10:53 by qumiraud         ###   ########.fr       */
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
