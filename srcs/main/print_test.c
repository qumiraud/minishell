












# include "../../includes/minishell.h"

void	print_tab(t_data *s_k)
{
	int	i;

	i = 0;
	while (s_k->rl_tab[i])
	{
		printf("rl_tab[%d]: %s\n",i, s_k->rl_tab[i]);
		// printf("%s", s_k->rl_tab[i]);
		i++;
	}
	// printf("\n");

	return ;
}

void	print_env(t_data *s_k)
{
	int	i;

	i = 0;
	while (s_k->tab_env[i])
	{
		printf("tab_env[%d]: %s\n", i, s_k->tab_env[i]);
		i++;
	}
	return;
}

void	print_all(t_data *s_k)
{
	print_tab(s_k);
	print_env(s_k);
	return;
}