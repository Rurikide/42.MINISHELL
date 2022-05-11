/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:03:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/11 11:54:44 by tshimoda         ###   ########.fr       */
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

void	fd_redirection(t_minishell *minishell)
{
	t_node *current;

 	current = minishell->head;


	// REDIRECTION INPUT
	if (current->fd_i != STDIN_FILENO)
	{
		dup2(current->fd_i, STDIN_FILENO);
		close(current->fd_i); // celui d'une redirection
	}
	else if (current->prev != NULL)
	{
		dup2(current->pipe_end[0], STDIN_FILENO);
		close(current->pipe_end[0]); // soit du infile ou bien celui du pipe_end[0]
	}
	// else
	// 	dup2(current->bu_stdin, STDIN_FILENO);
	
	// REDIRECTION OUTPUT : soit dans le stdout, soit dans une pipe ou soit dans un outfile finale.
	if (current->fd_o != STDOUT_FILENO)
	{
		dup2(current->fd_o, STDOUT_FILENO);
		close(current->fd_o);
	}
	else if (current->next != NULL)
	{
		dup2(current->pipe_end[1], STDOUT_FILENO);
		close(current->pipe_end[1]);
	}
	// else
	// 	dup2(current->bu_stdout, STDOUT_FILENO);
}