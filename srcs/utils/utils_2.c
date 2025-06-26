/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:55:22 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/26 11:10:22 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_whitespace(char **src)
{
	while (**src == ' ' || (**src >= 9 && **src <= 13))
		(*src)++;
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
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
