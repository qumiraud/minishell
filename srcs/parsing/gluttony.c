/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:20:50 by pjurdana          #+#    #+#             */
/*   Updated: 2025/04/28 09:45:40 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_tabs(t_data **s_k, char *str)
{
	fill_s_k_tab(s_k, str);
	fill_gluttony_tab(s_k, str);
}


int	glt_count_letters(char *str)
{
	int	i;
	int	word;
	int	quote;
	char	c;

	i = 0;
	word = 0;
	quote = 0;
	while (str[i] && word == 0)
	{
		while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		i++;
		if (str[i] && (str[i] != 32 || (str[i] <= 8 || str[i] >= 13)))
		{
			// word++;
			if (word == 1)
			return (i);
			quote = 0;
			while ((str[i] && (str[i] != 32 && (str[i] <= 8 || str[i] >= 13))))
			{
				if (str[i] == '\'' || str[i] == '"')
				{
					// printf("HALLO???\n\n\n");
					quote = 1;
					c = str[i];
					// printf("char c : %c\nstr[i + 1] : %c\nstr[i + 2] : %c\n", c, str[i +1], str[i + 2]);
					while (str[i])// && str[i] != c)//(str[i] != '\'' || str[i] != '"'))
					{
						i++;
						if (str[i] == c) //((str[i] == '\'' || str[i] == '"'))
						{
							quote = 0;
							while (str[i])
							{
								if (str[i] == 32 && (quote % 2) == 0)
								{
									quote = 0;
									break;
								}
								i++;
								if (str[i] == c) //((str[i] == '\'' || str[i] == '"'))
								{
									quote++;
								}
							}
						}
						if (quote == 0)
						{
							word++;
							if (word == 1)
								return (i);
							break ;
						}
					}
				}
				if(str[i] != '\0')
					i++;
			}
			word++;
		}
	}
	// printf ("i : %d\n", i);
	return (i);
}


int	glt_count_words(const char *str)
{

	int	i;
	int	word;
	int	quote;
	int	quotes = 0;
	char	c;

	i = 0;
	word = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
			i++;
		if (str[i] && (str[i] != 32 || (str[i] <= 8 || str[i] >= 13)))
		{
			word++;
			quote = 0;
			while ((str[i] && (str[i] != 32 && (str[i] <= 8 || str[i] >= 13))))
			{
				if (str[i] == '\'' || str[i] == '"')
				{
					quote = 1;
					c = str[i];
					while (str[i]) // && (str[i] != '\'' || str[i] != '"'))
					{
						i++;
						if (str[i] == c) //((str[i] == '\'' || str[i] == '"'))
						{
							while (str[i])
							{
								if (str[i] == 32 && (quotes % 2) == 0)
								{
									quote = 0;
									break;
								}
								i++;
								if (str[i] == c) //((str[i] == '\'' || str[i] == '"'))
								{
									quotes++;
								}
							}
						}
						if (quote == 0)
						{
							word++;
							break ;
						}
					}
				}
				if (str[i] != '\0')
					i++;
			}
		}
	}
	printf("\nword : %d\n\n", word);
	return (word);
}


void	glt_copy_word(char *dest, char **src, int count_l)
{
	int	i = 0;

	// printf ("count_l : %d\n", count_l);

	while (**src && i != count_l)// && !((**src >= 8 && **src <= 13) || **src == 32))
	{
		// if (**src == '"' && **src == '\'')
			// count_l++;
		// if (**src != '"' && **src != '\'')
		*dest++ = **src;
		// printf("dest : %c", *dest);
		(*src)++;
		i++;
	}
	*dest = '\0';
	while (**src && ((**src >= 8 && **src <= 13) || **src == 32))
		src++;
}




void	fill_gluttony_tab(t_data **s_k, char *str)
{
	int	i;
	int	count_l;
	int	count_w;

	i = 0;
	(*s_k)->tab_len = 0;
	count_w = 0;
	count_w = glt_count_words(str);
	printf ("count_w : %d\n\n", count_w);
	(*s_k)->glutto_tab = malloc(sizeof(char *) * (count_w + 1));
	while (str[0] == 32 || (str[0] >= 8  && str[0] <= 13 ))
	{
		str++;
	}
	while (str[0])
	{
		count_l = 0;
		count_l = glt_count_letters(str);
		printf ("count_l : %d\n", count_l);
		(*s_k)->glutto_tab[i] = malloc(sizeof(char) * (count_l + 1));
		glt_copy_word((*s_k)->glutto_tab[i], &str, count_l);
		if (count_l)
			i++;
		while (*str && ((*str >= 8 && *str <= 13) || *str == 32))
			str++;
	}
	(*s_k)->glutto_tab[i] = NULL;
	(*s_k)->tab_len = i;


}
