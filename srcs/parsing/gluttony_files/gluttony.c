/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:33:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/11 13:57:20 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	glt_copy_word(char *dest, char **src/*, int count_l*/)
{
	char quote;
	quote = 0;
	while (**src == ' ' || (**src >= 9 && **src <= 13))
		(*src)++;
	while (**src && (**src != ' ' && !(**src >= 9 && **src <= 13)))
	{
		if (**src == '|' || **src == '>' || **src == '<')
		{
			break ;
			// *dest = '\0';
			// return ;
		}
			if ((**src == '\'' || **src == '"') && quote == 0)
		{
			quote = **src;
			(*src)++;
			while (**src && **src != quote)
			{
				*dest++ = **src;
				(*src)++;
			}
			if (**src == quote)
			{
				(*src)++;
				quote = 0;
			}
		}
		else
		{
			*dest++ = **src;
			(*src)++;
		}
	}
	*dest = '\0';
	while (**src == ' ' || (**src >= 9 && **src <= 13))
		(*src)++;
}



// void	glt_copy_word(char *dest, char **src/*, int count_l*/)
// {
// 	char quote;

// 	quote = 0;
// 	while (**src == ' ' || (**src >= 9 && **src <= 13))
// 		(*src)++;
// 	while (**src && (**src != ' ' && !(**src >= 9 && **src <= 13)))
// 	{

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

void handle_standard_token(t_data **s_k, char **str, int *i)
{
	int len = glt_count_letters(*str);
	printf ("glt_letters : %d\n", len);
	if (len > 0)
	{
		(*s_k)->glutto_tab[*i] = malloc(len + 1);
		glt_copy_word((*s_k)->glutto_tab[*i], str);
		(*i)++;
	}
}

// gluttony.c (version corrigée)
void fill_gluttony_tab(t_data **s_k, char *str)
{
	int i = 0;
	(*s_k)->glutto_tab = malloc(sizeof(char *) * (glt_count_words(str) + (*s_k)->pipe_quo + 1));
	printf("glt_count_words = %d\n\n", glt_count_words(str));
	while (*str)
	{
		if (*str == '$' && *(str + 1) == '"')
		{ // Détection du motif $"
			// printf ("IIIIFFFFF\n\n\n\n\n\n");

			int len = find_closing_quote(str + 2, '"') + 3; // +3 pour $" et le "
			(*s_k)->glutto_tab[i] = ft_substr(str, 0, len);
			str += len;
			i++;
		}
		else if (*str == '<' && *(str + 1) == '<')
		{
			(*s_k)->glutto_tab[i++] = ft_strdup("<<");
			str += 2;
			// printf ("ELSE IFFFFF\n\n\n\n\n\n");
		}
		else if (*str == '>' && *(str + 1) == '>')
		{
			(*s_k)->glutto_tab[i++] = ft_strdup(">>");
			str += 2;
			// printf ("ELSE IFFFFF\n\n\n\n\n\n");
		}
		else if (*str == '<')
		{
			(*s_k)->glutto_tab[i++] = ft_strdup("<");
			str++;
			// printf ("ELSE IFFFFF\n\n\n\n\n\n");
		}
		else if (*str == '>')
		{
			(*s_k)->glutto_tab[i++] = ft_strdup(">");
			str++;
			// printf ("ELSE IFFFFF\n\n\n\n\n\n");
		}
		else if (*str == '|')
		{
			(*s_k)->glutto_tab[i++] = ft_strdup("|");
			str++;
			// printf ("ELSE IFFFFF\n\n\n\n\n\n");
		}
		else
		{
			// printf ("ELSEEEEEE\n\n\n\n\n\n");

			handle_standard_token(s_k, &str, &i);
		}
	}
	(*s_k)->glutto_tab[i] = NULL;
	(*s_k)->tab_len = i;

}


// void	fill_gluttony_tab(t_data **s_k, char *str)
// {
//     int i = 0;
//     // int in_pipe = 0;

//     (*s_k)->glutto_tab = malloc(sizeof(char *) * (glt_count_words(str) + 2));
//     while (*str) {
//         if (*str == '|') {
//             (*s_k)->glutto_tab[i++] = ft_strdup("|");
//             str++;
//             // in_pipe = 1;
//             while (*str == ' ') str++; // Ignore les espaces après le pipe
//         } else {
//             handle_standard_token(s_k, &str, &i);
//         }
//     }
//     (*s_k)->glutto_tab[i] = NULL;
// }
// void	fill_gluttony_tab(t_data **s_k, char *str)
// {
// 	int i = 0;
// 	int count_w = glt_count_words(str);

// 	(*s_k)->glutto_tab = malloc(sizeof(char *) * (count_w + 1));

// 	while (*str == ' ' || (*str >= 9 && *str <= 13))
// 		str++;

// 	while (*str)
// 	{
// 		if (*str == '|')
// 		{  // Détection explicite du pipe
//             (*s_k)->glutto_tab[i++] = ft_strdup("|");
//             str++;
//         }
// 		else
// 		{
// 			(*s_k)->glutto_tab[i] = malloc(sizeof(char) * (strlen(str) + 1));
// 			glt_copy_word((*s_k)->glutto_tab[i], &str);
// 			if (*((*s_k)->glutto_tab[i]))
// 				i++;

// 			while (*str == ' ' || (*str >= 9 && *str <= 13))
// 				str++;
// 		}
// 	}
// 	(*s_k)->glutto_tab[i] = NULL;
// 	(*s_k)->tab_len = i;
// }
