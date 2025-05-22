/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:34:30 by qumiraud          #+#    #+#             */
/*   Updated: 2025/05/22 16:34:53 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	init_echo_data(t_echo_data *data)
{
	data->i = 0;
	data->j = 0;
	data->n = 0;
	data->n_def = 1;
}

void	print_echo(char **str, int n_def, int i)
{

	while (str[i])
	{
		if (str[i][0] == '\\' && str[i][1] == '$')
			printf("$%s", str[i] + 2);

		else if (str[i][0] == '$' && str[i][1] != '\0')
		{
			if (str[i][1] == '=' || str[i][1] == '-' || str[i][1] == '+'
				|| str[i][1] == '/' || str[i][1] == '%' || str[i][1] == '.'
					|| str[i][1] == ',' || str[i][1] == ':' ||str[i][1] == '}'
						||str[i][1] == ']')
				printf("%s", str[i]);
			else if (getenv(str[i] + 1) != NULL)
				printf("%s", getenv(str[i] + 1));
		}
		// else if (str[i][0] == '$' && str[i][1] == '"')
		// {
		// 	len = strlen(str[i]);
		// 	if (len > 2)
		// 		write(1, &str[i][2], len - 3);
		// 	else
		// 		write(1, "", 0);
		// }

		else
			printf("%s", str[i]);
		if (str[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_def != 0)
		printf("\n");
}

int	ft_echo(char **str)
{
	t_echo_data	data;

	init_echo_data(&data);
	while (str[++data.i] && strncmp(str[data.i], "-n", 2) == 0)
	{
		data.n = 0;
		data.j = 0;
		while(str[data.i][2 + data.j] != '\0')
		{
			if (str[data.i][2 + data.j] == 'n')
				data.j++;
			else
			{
				data.n = 1;
				break;
			}
		}
		if (data.n == 1)
			break;
		else if (data.i == 1 && data.n == 0)
			data.n_def = data.n;
	}
	print_echo(str, data.n_def, data.i);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return (1);
// 	else
// 	{
// 		ft_echo(argv + 1);
// 		return (0);
// 	}
// }
