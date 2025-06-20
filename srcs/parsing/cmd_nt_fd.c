/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nt_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:11:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/20 09:43:25 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	else if (str[i] == '<' && str[i] == '<'
		&& str [i + 2] && !ft_isalpha((str[i + 2])))
		return (printf ("bash: syntax error near unexpected token `<<'\n"));
	else if (str[i] == '>' && str[i] == '>'
		&& str [i + 2] && !ft_isalpha((str[i + 2])))
		return (printf ("bash: syntax error near unexpected token `>>'\n"));
	else
		return (continue_cmd_nt_fd(str));
	return (0);
}
