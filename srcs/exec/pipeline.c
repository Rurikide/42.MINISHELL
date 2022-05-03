/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:03:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/03 16:07:50 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Je reçois les nodes avec les FD_IN et OUT
void    pipeline_main(t_minishell *minishell)
{
	t_node *current;

	current = minishell->head;
	while (current != NULL)
	{
		dup2(current->fd_in, STDIN_FILENO);
		close(current->fd_in);
		dup2(current->fd_out, STDOUT_FILENO);
		close(current->fd_out);
		current = current->next
	}
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
