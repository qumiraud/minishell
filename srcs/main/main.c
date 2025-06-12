/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:06 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/12 13:26:49 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	g_sig;


int	handle_readline(char *str, t_data **s_k, t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (*str)
		handle_str(str, s_k, cmd);
	len = (*s_k)->tab_len;
	if (*s_k)
	{
		if ((*s_k)->glutto_tab)
		{
			while (i <= len)
			{
				free((*s_k)->glutto_tab[i]);
				(*s_k)->glutto_tab[i] = NULL;
				i++;
			}
		}
		if ((*s_k)->glutto_tab)
		{
			free((*s_k)->glutto_tab);
			(*s_k)->glutto_tab = NULL;
		}
		if ((*s_k)->rl_tab)
		{
			free((*s_k)->rl_tab);
			(*s_k)->rl_tab = NULL;
		}
	}
	return (0);
}

int	validate_quotes_and_syntax(char *str, t_data **suprem_knowledge)
{
	if (quote_verif(str, suprem_knowledge) != 0)
	{
		str++;
		add_history(str);
		free((*suprem_knowledge)->str);
		return (1);
	}
	if (cmd_nt_fd(str) != 0)
	{
		str++;
		add_history(str);
		free((*suprem_knowledge)->str);
		return (1);
	}
	return (0);
}

int	process_command_line(t_data **suprem_knowledge, t_cmd *cmd)
{
	char	*str;

	str = readline("💾 minishell :");
	if (handle_exit_command(str, suprem_knowledge))
		return (1);
	if (handle_null_input(str, cmd, suprem_knowledge))
		return (1);
	process_input_string(&str, suprem_knowledge);
	if (validate_quotes_and_syntax(str, suprem_knowledge))
	{
		free(str);
		return (0);
	}
	pipe_quota(str, suprem_knowledge);
	if (handle_readline(str, suprem_knowledge, cmd) == 1)
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*suprem_knowledge;
	t_cmd	*cmd;
	int		result;

	cmd = NULL;
	if (check_arguments(argc, argv))
		return (1);
	init_suprem_knowledge(&suprem_knowledge, envp);
	if (!suprem_knowledge)
		return (1);
	while (1)
	{
		setup_signal();
		result = process_command_line(&suprem_knowledge, cmd);
		if (result == 1)
			break ;
	}
	handle_ending(&suprem_knowledge);
	return (0);
}
