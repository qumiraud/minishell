/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttonny_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:54:32 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/17 14:54:50 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_dollar_quote(t_data **s_k, char **str, int *i)
{
	int	len;

	len = find_closing_quote(*str + 2, '"') + 3;
	(*s_k)->glutto_tab[*i] = ft_substr(*str, 0, len);
	*str += len;
	(*i)++;
}

void	handle_double_redirect(t_data **s_k, char **str, int *i, char op)
{
	if (op == '<')
		(*s_k)->glutto_tab[(*i)++] = ft_strdup("<<");
	else
		(*s_k)->glutto_tab[(*i)++] = ft_strdup(">>");
	*str += 2;
}

void	handle_single_redirect(t_data **s_k, char **str, int *i, char op)
{
	if (op == '<')
		(*s_k)->glutto_tab[(*i)++] = ft_strdup("<");
	else if (op == '>')
		(*s_k)->glutto_tab[(*i)++] = ft_strdup(">");
	else if (op == '|')
		(*s_k)->glutto_tab[(*i)++] = ft_strdup("|");
	(*str)++;
}

void	process_character(t_data **s_k, char **str, int *i)
{
	if (**str == '$' && *(*str + 1) == '"')
		handle_dollar_quote(s_k, str, i);
	if (**str == '$' && *(*str + 1) == '\'')
		handle_dollar_quote(s_k, str, i);
	else if (**str == '<' && *(*str + 1) == '<')
		handle_double_redirect(s_k, str, i, '<');
	else if (**str == '>' && *(*str + 1) == '>')
		handle_double_redirect(s_k, str, i, '>');
	else if (**str == '<')
		handle_single_redirect(s_k, str, i, '<');
	else if (**str == '>')
		handle_single_redirect(s_k, str, i, '>');
	else if (**str == '|')
		handle_single_redirect(s_k, str, i, '|');
	else
		handle_standard_token(s_k, str, i);
}

void	fill_gluttony_tab(t_data **s_k, char *str)
{
	int	i;

	i = 0;
	if (!allocate_glutto_tab(s_k, str))
		return ;
	while (*str)
	{
		process_character(s_k, &str, &i);
	}
	(*s_k)->glutto_tab[i] = NULL;
	(*s_k)->tab_len = i;
	printf ("valor I : %d\n\n\n\n\n\n", i);
}