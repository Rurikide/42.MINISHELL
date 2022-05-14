/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:10:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/13 21:00:09 by tshimoda         ###   ########.fr       */
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
		minishell.in_pipeline = NO;
		minishell.user_input = NULL;
		minishell.options = NULL;
		minishell.head = NULL;
	}
	return (&minishell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_node *current;

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
		if (minishell->user_input == CTRL_D)
			ctrl_d_exit();
		if (minishell->user_input[0] != '\0')
		{
			add_history(minishell->user_input);
			ms_parsing();
			current = minishell->head;
			//t_node *print;
			// print = minishell->head;
			
			// while (print)
			// {
			// 	printf("print value == %s\n", print->value);
			// 	print = print->next;
			// }
			execution_main(current);
			ms_freeList(minishell->head);
			minishell->head = NULL;
		}
	}
	return (0);
}

void	ms_freelist(t_node *head)
{
	t_node *tmp;

	while (head != NULL)
	{
		tmp = head;
		free(tmp->value);
		head = head->next;
		free(tmp);
	}
}
