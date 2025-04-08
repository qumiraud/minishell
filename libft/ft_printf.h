/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:45:24 by qumiraud          #+#    #+#             */
/*   Updated: 2024/11/05 11:50:58 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(const char *str, ...);
int	ft_selectpf(va_list args, char c);
int	ft_putcharpf_fd(char c, int fd);
int	ft_printstr(char *s, int fd);
int	ft_printphexanbr(unsigned long int nbr);
int	ft_printuphexanbr(unsigned int nbr);
int	ft_printhexanbr(unsigned int nbr);
int	ft_printunsnbr(unsigned int nbr);
int	ft_printnbr(int nbr);
int	ft_voidpointer(unsigned long int nbr);

#endif
