/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:31:22 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/25 18:32:09 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_echo_data(t_echo_data *data)
{
	data->i = 0;
	data->j = 0;
	data->n = 0;
	data->n_def = 1;
}

void	handle_escaped_dollar(char *str)
{
	printf("$%s", str + 2);
}

void	handle_special_chars(char *str)
{
	if (str[1] == '=' || str[1] == '-' || str[1] == '+'
		|| str[1] == '/' || str[1] == '%' || str[1] == '.'
		|| str[1] == ',' || str[1] == ':' || str[1] == '}'
		|| str[1] == ']')
		printf("%s", str);
	else if (getenv(str + 1) != NULL)
		printf("%s", getenv(str + 1));
	else if (getenv(str + 1) == NULL)
		printf("%s", getenv(str + 1));
}

void	handle_exit_code(void)
{
	printf("%d", g_status);
}

void	handle_quoted_variable(char *str)
{
	int	len;

	len = strlen(str);
	if (len > 3)
		printf("%.*s", len - 3, str + 2);
	else
		printf("\n");
}
