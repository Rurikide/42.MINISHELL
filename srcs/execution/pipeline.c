/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:03:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/13 16:48:21 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Je reçois les nodes avec les FD_IN et OUT
void    pipeline_open(t_minishell *minishell)
{
	t_node *current;

	current = minishell->head;
	// while (current != NULL)
	// {
	// 	dup2(current->fd_i, STDIN_FILENO);
	// 	close(current->fd_i);
	// 	dup2(current->fd_o, STDOUT_FILENO);
	// 	close(current->fd_o);
	// 	current = current->next
	// }
	while (current != NULL)
	{
		//
		if (pipe(current->pipe_end) == FAIL)
			printf("the pipe didn't work\n");
		//
		current = current->next;
	}
}