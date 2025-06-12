/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:33:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/12 10:28:04 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	skip_whitespace(char **src)
{
	while (**src == ' ' || (**src >= 9 && **src <= 13))
		(*src)++;
}

static int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

static void	copy_quoted_content(char *dest, char **src, char quote)
{
	(*src)++;
	while (**src && **src != quote)
	{
		*dest++ = **src;
		(*src)++;
	}
	if (**src == quote)
	{
		(*src)++;
	}
}

static int	handle_quote_case(char *dest, char **src, char *quote)
{
	if ((**src == '\'' || **src == '"') && *quote == 0)
	{
		*quote = **src;
		copy_quoted_content(dest, src, *quote);
		*quote = 0;
		return (1);
	}
	return (0);
}

static int	should_continue_copying(char **src)
{
	if (!**src)
		return (0);
	if (**src == ' ' || (**src >= 9 && **src <= 13))
		return (0);
	if (is_operator(**src))
		return (0);
	return (1);
}

void	glt_copy_word(char *dest, char **src)
{
	char	quote;
	char	*dest_start;

	quote = 0;
	dest_start = dest;
	skip_whitespace(src);
	while (should_continue_copying(src))
	{
		if (!handle_quote_case(dest_start, src, &quote))
		{
			*dest_start++ = **src;
			(*src)++;
		}
	}
	*dest_start = '\0';
	skip_whitespace(src);
}

// void	glt_copy_word(char *dest, char **src)
// {
// 	char	quote;

// 	quote = 0;
// 	while (**src == ' ' || (**src >= 9 && **src <= 13))
// 		(*src)++;
// 	while (**src && (**src != ' ' && !(**src >= 9 && **src <= 13)))
// 	{
// 		if (**src == '|' || **src == '>' || **src == '<')
// 			break ;
// 		if ((**src == '\'' || **src == '"') && quote == 0)
// 		{
// 			quote = **src;
// 			(*src)++;
// 			while (**src && **src != quote)
// 			{
// 				*dest++ = **src;
// 				(*src)++;
// 			}
// 			if (**src == quote)
// 			{
// 				(*src)++;
// 				quote = 0;
// 			}
// 		}
// 		else
// 		{
// 			*dest++ = **src;
// 			(*src)++;
// 		}
// 	}
// 	*dest = '\0';
// 	while (**src == ' ' || (**src >= 9 && **src <= 13))
// 		(*src)++;
// }

void	handle_standard_token(t_data **s_k, char **str, int *i)
{
	int	len;

	len = glt_count_letters(*str);
	printf ("LEN : %d\n\n\n", len);
	if (len > 0)
	{
		(*s_k)->glutto_tab[*i] = malloc(len + 1);
		glt_copy_word((*s_k)->glutto_tab[*i], str);
		(*i)++;
	}
}

static int	allocate_glutto_tab(t_data **s_k, char *str)
{
	(*s_k)->glutto_tab = malloc(sizeof(char *)
			* (glt_count_words(str) + (*s_k)->pipe_quo + 2));
	if (!(*s_k)->glutto_tab)
		return (0);
	return (1);
}

static void	handle_dollar_quote(t_data **s_k, char **str, int *i)
{
	int	len;

	len = find_closing_quote(*str + 2, '"') + 3;
	(*s_k)->glutto_tab[*i] = ft_substr(*str, 0, len);
	*str += len;
	(*i)++;
}

static void	handle_double_redirect(t_data **s_k, char **str, int *i, char op)
{
	if (op == '<')
		(*s_k)->glutto_tab[(*i)++] = ft_strdup("<<");
	else
		(*s_k)->glutto_tab[(*i)++] = ft_strdup(">>");
	*str += 2;
}

static void	handle_single_redirect(t_data **s_k, char **str, int *i, char op)
{
	if (op == '<')
		(*s_k)->glutto_tab[(*i)++] = ft_strdup("<");
	else if (op == '>')
		(*s_k)->glutto_tab[(*i)++] = ft_strdup(">");
	else if (op == '|')
		(*s_k)->glutto_tab[(*i)++] = ft_strdup("|");
	(*str)++;
}

static void	process_character(t_data **s_k, char **str, int *i)
{
	if (**str == '$' && *(*str + 1) == '"')
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

// void	fill_gluttony_tab(t_data **s_k, char *str)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	(*s_k)->glutto_tab = malloc(sizeof(char *) * (glt_count_words(str) + (*s_k)->pipe_quo + 2));
// 	while (*str)
// 	{
// 		if (*str == '$' && *(str + 1) == '"')
// 		{
// 			len = find_closing_quote(str + 2, '"') + 3;
// 			(*s_k)->glutto_tab[i] = ft_substr(str, 0, len);
// 			str += len;
// 			i++;
// 		}
// 		else if (*str == '<' && *(str + 1) == '<')
// 		{
// 			(*s_k)->glutto_tab[i++] = ft_strdup("<<");
// 			str += 2;
// 		}
// 		else if (*str == '>' && *(str + 1) == '>')
// 		{
// 			(*s_k)->glutto_tab[i++] = ft_strdup(">>");
// 			str += 2;
// 		}
// 		else if (*str == '<')
// 		{
// 			(*s_k)->glutto_tab[i++] = ft_strdup("<");
// 			str++;
// 		}
// 		else if (*str == '>')
// 		{
// 			(*s_k)->glutto_tab[i++] = ft_strdup(">");
// 			str++;
// 		}
// 		else if (*str == '|')
// 		{
// 			(*s_k)->glutto_tab[i++] = ft_strdup("|");
// 			str++;
// 		}
// 		else
// 			handle_standard_token(s_k, &str, &i);
// 	}
// 	(*s_k)->glutto_tab[i] = NULL;
// 	(*s_k)->tab_len = i;
// }
