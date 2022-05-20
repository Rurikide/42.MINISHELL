/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:10:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/19 22:59:47 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_minishell *minishell)
{
	t_node	*current;

	if (minishell->user_input != NULL)
		free(minishell->user_input);
	minishell->user_input = readline("minishell> ");
	if (minishell->user_input == CTRL_D)
		ctrl_d_exit();
	if (minishell->user_input[0] != '\0')
	{
		add_history(minishell->user_input);
		if (ms_parsing(0))
		{
			current = minishell->head;
			execution_main(current);
			ms_free_list(minishell->head);
			minishell->head = NULL;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	init_env(env);
	minishell = get_minishell();
	set_signals();
	while (true)
	{
		minishell_loop(minishell);
	}
	return (0);
}
