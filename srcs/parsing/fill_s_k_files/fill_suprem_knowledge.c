/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_suprem_knowledge.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:44:14 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/26 13:39:53 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	fill_suprem_knowledge(t_data **s_k, char *str)
{
	if (!s_k || !(*s_k))
		return ;
	fill_tabs(s_k, str);
}

void	copy_word(char *dest, char **src, int count_l)
{
	int	i;

	i = 0;
	while (**src && i != count_l)
	{
		if (**src == '"' && **src == '\'')
			count_l++;
		if (**src != '"' && **src != '\'')
			*dest++ = **src;
		(*src)++;
		i++;
	}
	*dest = '\0';
	while (**src && ((**src >= 8 && **src <= 13) || **src == 32))
		src++;
}

void	fill_s_k_tab(t_data **s_k, char *str)
{
	int	i;
	int	count_l;
	int	count_w;

	i = 0;
	(*s_k)->tab_len = 0;
	count_w = 0;
	count_w = count_words(str);
	(*s_k)->rl_tab = malloc(sizeof(char *) * (count_w + 1));
	while (str[0] == 32 || (str[0] >= 8 && str[0] <= 13))
		str++;
	while (str[0])
	{
		while (*str && ((*str >= 8 && *str <= 13) || *str == 32))
			str++;
		count_l = 0;
		count_l = count_letters(str);
		(*s_k)->rl_tab[i] = malloc(sizeof(char) * (count_l + 1));
		copy_word((*s_k)->rl_tab[i], &str, count_l);
		i++;
		while (*str && ((*str >= 8 && *str <= 13) || *str == 32))
			str++;
	}
	(*s_k)->rl_tab[i] = NULL;
	(*s_k)->tab_len = i;
}

void	init_suprem_knowledge(t_data **s_k, char **envp)
{
	(*s_k) = malloc(sizeof(t_data));
	if (!s_k)
	{
		printf("damned\n");
		return ;
	}
	(*s_k)->rl_tab = NULL;
	(*s_k)->glutto_tab = NULL;
	(*s_k)->re_token = NULL;
	(*s_k)->tab_env = NULL;
	(*s_k)->pipe_nbr = 0;
	*(*s_k)->pipefd1 = 0;
	*(*s_k)->pipefd2 = 0;
	(*s_k)->stat_quo = 0;
	(*s_k)->pipe_quo = 0;
	(*s_k)->in_quo = 0;
	fill_tab_env(s_k, envp);
	(*s_k)->tab_len = 0;
}
