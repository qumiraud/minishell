/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glt_letters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:27:20 by pjurdana          #+#    #+#             */
/*   Updated: 2025/06/19 10:52:55 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_redirections(char *str, int i, int *inc)
{
	*inc = 0;
	if (i == 0)
	{
		if (handle_double_redir(str, i, inc))
			return (i + *inc);
		if (handle_single_redir(str, i, inc))
			return (i + *inc);
	}
	else
	{
		if (handle_double_redir(str, i, inc))
			return (i);
		if (handle_single_redir(str, i, inc))
			return (i);
	}
	return (0);
}

int	process_word_part2(char *str, int *i, int *word, int redir_pos)
{
	int	inc;

	if (redir_pos > 0)
	{
		if (*i != 0 && (str[*i] == '>' || str[*i] == '<' || str[*i] == '|'
				|| (str[*i] == '>' && str[*i + 1] == '>')
				|| (str[*i] == '<' && str[*i + 1] == '<')))
		{
			*word = redir_pos;
			handle_redirections(str, *i, &inc);
			*i += inc;
			return (*word);
		}
		return (redir_pos);
	}
	return (0);
}

int	glt_process_word(char *str, int *i, int *word)
{
	int	redir_pos;
	int	result;
	int	inc;

	while ((str[*i] && (str[*i] != 32 && (str[*i] <= 8 || str[*i] >= 13))))
	{
		redir_pos = handle_redirections(str, *i, &inc);
		result = process_word_part2(str, i, word, redir_pos);
		if (result > 0)
			return (result);
		if (str[*i] == '\'' || str[*i] == '"')
			return (handle_quotes(str, i, word));
		if (str[*i] != '\0')
			(*i)++;
	}
	return (0);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == 32 || (str[*i] >= 8 && str[*i] <= 13))
		(*i)++;
}

int	glt_count_letters(char *str)
{
	int	i;
	int	word;
	int	result;

	i = 0;
	word = 0;
	while (str[i] && word == 0)
	{
		skip_spaces(str, &i);
		if (str[i] && (str[i] != 32 || (str[i] <= 8 || str[i] >= 13)))
		{
			if (word == 1)
				return (i);
			result = glt_process_word(str, &i, &word);
			if (result > 0)
			{
				// printf ("HEEEEEEERRRREEEEEE\n\n\n");
				// printf ("IIIIIIII %d\n\n\n", i);
				return (result);
			}
			word++;
		}
	}
	// printf ("IIIIIIII %d\n\n\n", i);

	return (i);
}


// int	glt_count_letters(char *str)
// {
// 	int	i;
// 	int	word;
// 	int	quote;
// 	char	c;

// 	i = 0;
// 	word = 0;
// 	quote = 0;
// 	printf("IIIII : %d\n\n", i);
// 	while (str[i] && word == 0)
// 	{
// 		while (str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
// 		{
// 			// str++;
// 			i++;
// 		}
// 		if (str[i] && (str[i] != 32 && (str[i] <= 8 || str[i] >= 13)))
// 		{
// 			// word++;
// 			if (word == 1)
// 			{
// 				// printf ("i : %d\n", i);
// 				return (i);
// 			}
// 			quote = 0;
// 			while ((str[i] && (str[i] != 32 && (str[i] <= 8 || str[i] >= 13))))
// 			{
// 					printf ("str[%c]\n\n", str[i]);
				
// 				if (str[i] == '\'' || str[i] == '"')
// 				{
// 					// printf("HALLO???\n\n\n");
// 					quote = 1;
// 					c = str[i];
// 					printf ("str\"[%c]\"\n\n", str[i]);
// 					// printf("char c : %c\nstr[i + 1] : %c\nstr[i + 2] : %c\n", c, str[i +1], str[i + 2]);
// 					while (str[i])// && str[i] != c)//(str[i] != '\'' || str[i] != '"'))
// 					{
// 						printf ("str\"[%c]\"\n\n", str[i]);
// 						i++;
// 						// str++;
// 						if (str[i] == c) //((str[i] == '\'' || str[i] == '"'))
// 						{
// 							quote = 0;
// 							while (str[i])
// 							{
// 								printf ("str\"[%c]\"\n\n", str[i]);
// 								if (str[i] == 32 && (quote % 2) == 0)
// 								{
// 									quote = 0;
// 									break ;
// 								}
// 								i++;
// 								str++;
// 								if (str[i] == c) //((str[i] == '\'' || str[i] == '"'))
// 								{
// 									quote++;
// 								}
// 							}
// 						}
// 						if (quote == 0)
// 						{
// 							printf ("ALORSSSSSSSSS????\n\n\n\n\n\n");
// 							word++;
// 							if (word == 1)
// 							{
// 								// printf ("i : %d\n", i);
// 								return (i);
// 							}
// 							break ;
// 						}
// 					}
// 				}
// 				if(str[i] != '\0')
// 				{
// 					i++;
// 					// str++;
// 				}
// 			}
// 			word++;
// 		}
// 	}
// 	// printf ("i : %d\n", i);
// 	return (i);
// }


