/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nt_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:11:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/23 14:57:25 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	continue_cmd_nt_fd_2(char *str)
{
	int	i = 0;
	int	x = 0;
	while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		i++;
	while (ft_isalpha(str[i]))
		i++;
	while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '<' || str[i] == '>')
	{
		while (i++ && (str[i] == 32 || (str[i] >= 8 && str[i] <= 13)))
			x = 1;
		if (str[i] == '>' && x == 1)
			return (printf("bash: syntax error near unexpected token `>'\n"));
		else if (str[i] == '<' && x == 1)
			return (printf("bash: syntax error near unexpected token `<'\n"));
	}
	return (0);
}

int	continue_cmd_nt_fd(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == ';' && str[i + 1] == ';')
		return (printf("bash: syntax error near unexpected token `;;'\n"));
	else if (str[i] == '&' && str[i + 1] == '&')
		return (printf("bash: syntax error near unexpected token `&&'\n"));
	else if (str[i] == '&')
		return (printf("bash: syntax error near unexpected token `&'\n"));
	else if (str[i] == ';')
		return (printf("bash: syntax error near unexpected token `;'\n"));
	else if ((str[i] == '(' || str[i] == ')'))
		return (printf("bash: syntax error near unexpected token `)'\n"));
	else
		return (continue_cmd_nt_fd_2(str));

	return (0);
}

int	cmd_nt_fd(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '|' && str[i + 1] == '|')
		return (printf("bash: syntax error near unexpected token `||'\n"));
	else if (str[i] == '|')
		return (printf("bash: syntax error near unexpected token `|'\n"));
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>' )
		return (printf ("bash: syntax error near unexpected token `>'\n"));
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<' )
		return (printf ("bash: syntax error near unexpected token `<'\n"));
	else if (str[i] == '<' && str[i + 1] == '<'
		&& str [i + 2] && str[i + 2] == ' ' && !ft_isalpha((str[i + 3])))
		return (printf ("bash: syntax error near unexpected token `<<'\n"));
	else if (str[i] == '>' && str[i] == '>'
		&& str [i + 2] && !ft_isalpha((str[i + 2])))
		return (printf ("bash: syntax error near unexpected token `>>'\n"));
	else
		return (continue_cmd_nt_fd(str));
	return (0);
}
