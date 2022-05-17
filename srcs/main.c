/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:10:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/17 15:01:46 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
			execution_main(current);
			ms_freeList(minishell->head);
			minishell->head = NULL;
		}
	}
	return (0);
}
			//t_node *print;
			// print = minishell->head;
			
			// while (print)
			// {
			// 	printf("print value == %s\n", print->value);
			// 	print = print->next;
			// }

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


void	ms_freelist_version2(t_node *head)
{
	t_node *tmp;

	while (head != NULL)
	{
		tmp = head->next;
		if (head->value != NULL)
			free(head->value);
		if (head->eof != NULL)
			free(head->eof);
		if (head != NULL)
			free(head);
		head = tmp;
	}
}
