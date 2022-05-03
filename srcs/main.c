/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:10:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/03 15:38:59 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_minishell	*get_minishell(void)
{
	static t_minishell	minishell;

	if (minishell.init != 1)
	{
		minishell.init = 1;
		minishell.shlvl = 1;
		minishell.env = NULL;
		minishell.env_size = 0;
		minishell.exit_nb = 0;
		minishell.user_input = NULL;
		minishell.options = NULL;
		minishell.head = NULL;
	}
	return (&minishell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char		**options;

	(void)argc;
	(void)argv;
	init_env(env);
	minishell = get_minishell();
	set_signals();

	while (true)
	{
		if (minishell->user_input != NULL)
			free(minishell->user_input);
		minishell->user_input = readline("minishell> ");
		add_history(minishell->user_input);
		if (minishell->user_input == CTRL_D)
			ctrl_d_exit();

		// else if (ft_strcmp(minishell->user_input, "heredoc") == SUCCESS)
		// 	here_document("FIN");
			
		if (minishell->options != NULL)
			ft_free_table(minishell->options);
		options = ft_split(minishell->user_input, ' ');
		minishell->options = options;

		if (execution_builtins(options) == NO)
		{
			execution_access(options);
		}
	}
	return (0);
}


/* minishell_loop planning
	set_signals prealablement
	user_input = readline
	t_node = parsing
	heredoc remplace la value qui est un char *
	



*/