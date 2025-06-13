/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:06 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/13 14:01:15 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_status;

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
	// printf("Halloooo\n\n\n\n");

	// handle_ending(&suprem_knowledge);
	return (0);
}
