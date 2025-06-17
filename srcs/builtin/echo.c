/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:34:30 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/17 15:41:49 by pjurdana         ###   ########.fr       */
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

void handle_escaped_dollar(char *str)
{
    printf("$%s", str + 2);
}

void handle_special_chars(char *str)
{
    if (str[1] == '=' || str[1] == '-' || str[1] == '+' ||
        str[1] == '/' || str[1] == '%' || str[1] == '.' ||
        str[1] == ',' || str[1] == ':' || str[1] == '}' ||
        str[1] == ']')
    {
        printf("%s", str);
    }
    else if (getenv(str + 1) != NULL)
    {
        printf("%s", getenv(str + 1));
    }
}

void handle_exit_code(void)
{
    printf("exit code a venir\n");
}

void handle_quoted_variable(char *str)
{
    int len = strlen(str);
    if (len > 3)
        printf("%.*s", len - 3, str + 2);
    else
        printf("\n");
}

int should_process_variable(char *str)
{
    return (str[0] == '$' && str[1] != '\0' &&
            str[1] != '\'' && str[1] != '"' && str[1] != '?');
}

void process_token_echo(char *str)
{
    if (str[0] == '\\' && str[1] == '$')
        handle_escaped_dollar(str);
    else if (should_process_variable(str))
        handle_special_chars(str);
    else if (str[0] == '$' && str[1] == '?')
        handle_exit_code();
    else if (str[0] == '$' && (str[1] == '"' || str[1] == '\''))
        handle_quoted_variable(str);
    else
        printf("%s", str);
}

void print_echo(char **str, int n_def, int i)
{
    while (str[i])
    {
        process_token_echo(str[i]);
        if (str[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (n_def != 0)
        printf("\n");
}


// void	print_echo(char **str, int n_def, int i)
// {

// 	while (str[i])
// 	{
// 		if (str[i][0] == '\\' && str[i][1] == '$')
// 			printf("$%s", str[i] + 2);

// 		else if (str[i][0] == '$' && str[i][1] != '\0' && str[i][1] != '\'' && str[i][1] != '"' && str[i][1] != '?')
// 		{
// 			if (str[i][1] == '=' || str[i][1] == '-' || str[i][1] == '+'
// 				|| str[i][1] == '/' || str[i][1] == '%' || str[i][1] == '.'
// 					|| str[i][1] == ',' || str[i][1] == ':' ||str[i][1] == '}'
// 						||str[i][1] == ']')
// 				printf("%s", str[i]);
// 			else if (getenv(str[i] + 1) != NULL)
// 				printf("%s", getenv(str[i] + 1));
// 		}
// 		else if (str[i][0] == '$' && str[i][1] == '?')
// 		{
// 			printf("exit code a venir\n");
// 		}
// 		else if (str[i][0] == '$' && str[i][1] == '"')
// 		{
// 			int len = strlen(str[i]);
// 			if (len > 3) // $"..." avec au moins un caractère entre les guillemets
// 				printf("%.*s", len - 3, str[i] + 2);
// 			else
// 				printf("\n"); // Cas $""
// 		}

// 		else
// 			printf("%s", str[i]);
// 		if (str[i + 1] != NULL)
// 			printf(" ");
// 		i++;
// 	}
// 	if (n_def != 0)
// 		printf("\n");
// }

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
