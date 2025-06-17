/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:01:56 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/17 16:20:54 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void	ft_exit(int err_value)
{
	g_status = err_value;
	if (g_status > 255)
		g_status -= 255;
	exit(g_status);
}