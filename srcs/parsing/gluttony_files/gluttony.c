/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:33:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/18 17:58:11 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_quote_case(char *dest, char **src, char *quote)
{
	if ((**src == '\'' || **src == '"') && *quote == 0)
	{
		printf ("ALED\n\n\n");
		*quote = **src;
		while (**src)
		{
			if (**src == *quote)
			{
				(*src)++;
				break ;
			}
			*dest++ = **src;
			(*src)++;
		}
		*quote = 0;
		return (1);
	}
	return (0);
}

int	should_continue_copying(char **src)
{
	if (!**src)
		return (0);
	// if (**src == ' ' || (**src >= 9 && **src <= 13))
		// return (0);
	if (is_operator(**src))
		return (0);
	return (1);
}

void	glt_copy_word(char *dest, char **src, int count_l)
{
	char	quote;
	char	*dest_start;
	int	i = 0;


	quote = 0;
	dest_start = dest;
	skip_whitespace(src);
	while (should_continue_copying(src) && i != count_l)
	{
		i++;
		if (!handle_quote_case(dest_start, src, &quote))
		{
			*dest_start++ = **src;
			(*src)++;
		}
	}
	printf ("ICIIIIIIIII : %d\n", i);
	*dest_start = '\0';
	skip_whitespace(src);
}

// void	glt_copy_word(char *dest, char **src, int count_l)
// {
// 	int	i = 0;

// 	// printf ("count_l : %d\n", count_l);

// 	while (**src && i != count_l)// && !((**src >= 8 && **src <= 13) || **src == 32))
// 	{
// 		// if (**src == '"' && **src == '\'')
// 			// count_l++;
// 		// if (**src != '"' && **src != '\'')
// 		*dest++ = **src;
// 		// printf("dest : %c", *dest);
// 		(*src)++;
// 		i++;
// 	}
// 	*dest = '\0';
// 	while (**src && ((**src >= 8 && **src <= 13) || **src == 32))
// 		src++;
// }




void	handle_standard_token(t_data **s_k, char **str, int *i)
{
	int	len;
	// int x = 0;

	len = glt_count_letters(*str);
	printf ("LETTERS : %d\n\n\n", len);
	printf ("str - > %s\n\n", *str);
	if (len > 0)
	{
		(*s_k)->glutto_tab[*i] = malloc(len + 1);
		glt_copy_word((*s_k)->glutto_tab[*i], str, len);
		(*i)++;
		// while (len > x)
		// {
		// 	str++;
		// 	x++;
		// }
	}
	// else
		// exit (0);
	// printf ("IIIIIIII %d\n\n\n", *i);
}

int	allocate_glutto_tab(t_data **s_k, char *str)
{
	(*s_k)->glutto_tab = malloc(sizeof(char *)
			* (glt_count_words(str) + (*s_k)->pipe_quo + 2));
	if (!(*s_k)->glutto_tab)
		return (0);
	return (1);
}
