/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:03:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/04 12:41:18 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Je reçois les nodes avec les FD_IN et OUT
void    pipeline_open(t_minishell *minishell)
{
	t_node *current;

	current = minishell->head;
	while (current != NULL)
	{
		dup2(current->fdI, STDIN_FILENO);
		close(current->fdI);
		dup2(current->fdO, STDOUT_FILENO);
		close(current->fdO);
		current = current->next
	}
	/*
		ou faire plutôt

		int pipe_end[2];

		while (current != NULL)
		{
			pipe(pipe_end);
			current = current->next;
		}
	*/
}

void	pipeline_close(void)
{
	/*
		while (current)
		{
			close(current->fd_i);
			close(current->fd_o);
			current = current->next;
		}
	*/
}
