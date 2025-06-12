/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:41:06 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/12 13:21:15 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sig;

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	while (cmd)
	{
		tmp = cmd->next;
		while (i < cmd->argc)
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			i++;
		}
		i = 0;
		free(cmd->input_file);
		free(cmd->output_file);
		free(cmd);
		cmd = tmp;
	}
}

void	handle_str(char *str, t_data **s_k, t_cmd *cmd)
{
	str++;
	add_history(str);
	fill_suprem_knowledge(s_k, str);
	cmd = parse_cmd((*s_k)->glutto_tab);
	print_tab(*s_k);
	print_command_list(cmd);
	handle_exec(*s_k, cmd);
	// free_cmd(cmd);
	// print_command_list(cmd);
}

void	handle_ending(t_data **s_k)
{
	free_s_k(s_k);
	free_glt(s_k);
	free(*s_k);
	(*s_k) = NULL;
	printf("exit\n");
}

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

char	*input_with_space(char *str)
{
	char	*new_str;

	new_str = NULL;
	if (!str)
		return (NULL);
	new_str = ft_strjoin(" ", str);
	if (!new_str)
		return (NULL);
	free (str);
	str = NULL;
	return (new_str);
}





// int	main(int argc, char **argv, char **envp)
// {
// 	t_data		*suprem_knowledge;
// 	t_cmd		*cmd;
// 	char		*str;

// 	str = NULL;
// 	cmd = NULL;
// 	if (argc > 1)
// 	{
// 		argv[0] = NULL;
// 		return (1);
// 	}
// 	init_suprem_knowledge(&suprem_knowledge, envp);
// 	if (!suprem_knowledge)
// 		return (1);
// 	while (1)
// 	{
// 		setup_signal();
// 		str = readline("💾 minishell :");
// 		if (ft_strcmp(str, "exit") == 1)
// 		{
// 			free (str);
// 			str = NULL;
// 			handle_ending(&suprem_knowledge);
// 			return (0);
// 		}
// 		if (!str)
// 		{
// 			printf("exit\n");
// 			free_cmd (cmd);
// 			handle_ending(&suprem_knowledge);
// 			return (0);
// 		}
// 		if (str && str[0] != 0)
// 		{
// 			str = input_with_space(str);
// 			suprem_knowledge->str = str;
// 		}
// 		if (quote_verif(str, &suprem_knowledge) != 0)
// 		{
// 			str++;
// 			add_history(str);
// 			free (suprem_knowledge->str);
// 			continue ;
// 		}
// 		pipe_quota(str, &suprem_knowledge);
// 		if (cmd_nt_fd(str) != 0)
// 		{
// 			str++;
// 			add_history(str);
// 			free(suprem_knowledge->str);
// 			continue ;
// 		}
// 		if (handle_readline(str, &suprem_knowledge, cmd) == 1)
// 			break ;
// 		free (str);
// 		str = NULL;
// 	}
// 	handle_ending(&suprem_knowledge);
// 	return (0);
// }



int	check_arguments(int argc, char **argv)
{
	if (argc > 1)
	{
		argv[0] = NULL;
		return (1);
	}
	return (0);
}

int	handle_exit_command(char *str, t_data **suprem_knowledge)
{
	if (ft_strcmp(str, "exit") == 1)
	{
		free(str);
		handle_ending(suprem_knowledge);
		return (1);
	}
	return (0);
}

int	handle_null_input(char *str, t_cmd *cmd, t_data **suprem_knowledge)
{
	if (!str)
	{
		printf("exit\n");
		free_cmd(cmd);
		handle_ending(suprem_knowledge);
		return (1);
	}
	return (0);
}

void	process_input_string(char **str, t_data **suprem_knowledge)
{
	if (*str && (*str)[0] != 0)
	{
		*str = input_with_space(*str);
		(*suprem_knowledge)->str = *str;
	}
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
