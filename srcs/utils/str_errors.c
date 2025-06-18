/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:09:06 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/18 18:02:25 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	str_error(char *str, char *cmd_args, char *msg)
{
	int	len;

	if (cmd_args)
		len = ft_strlen(cmd_args);
	write(2, str, ft_strlen(str));
	if (cmd_args && cmd_args[0] != '\0')
	{
		write(2, cmd_args, len);
		write(2, " : ", 3);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
