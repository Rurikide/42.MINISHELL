/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:40:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/13 19:10:01 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

void execution_main(t_node *current)
{
    char **options;
	int i;

	i = 0;
	printf("node value = %s\n", current->value);
	options = ft_split(current->value, ' ');
	printf("option0 = %s\n", options[0]);
	printf("option1 = %s\n", options[1]);
    if (current->next == NULL && is_a_builtin(options) == YES)
	{
		prepare_exec_one_builtin(current, options);
	}
	else if(current != NULL)
	{
		pipeline_fork(current, current->fd_i);
	}
}

void	prepare_exec_one_builtin(t_node *current, char **options)
{
	int bu_fd_in;
	int bu_fd_out;

	bu_fd_in = dup(STDIN_FILENO);
	bu_fd_out = dup(STDOUT_FILENO);
	
	if (current->fd_i != STDIN_FILENO)
	{
		//
	//	printf("redirecting std_IN for current->fd_in #%d\n", current->fd_i);
		//
		dup2(current->fd_i, STDIN_FILENO);
		close(current->fd_i);
	}
	if (current->fd_o != STDOUT_FILENO)
	{
		//
	//	printf("redirecting std_OUT for current->fd_out #%d\n", current->fd_o);
		//
		dup2(current->fd_o, STDOUT_FILENO);
		close(current->fd_o);
	}
	execution_builtins(current, options);
	dup2(bu_fd_in, STDIN_FILENO);
	dup2(bu_fd_out, STDOUT_FILENO);
	close(bu_fd_in);
	close(bu_fd_out);
}

void	pipeline_fork(t_node *current, int read_fd)
{
	int pipe_end[2];
	char **options;
	pid_t id;
	
	if (pipe(pipe_end) == FAIL)
		printf("Error creating pipe\n");
	id = fork();
	if (id == FAIL)
		printf("Error making fork\n");
	if (id == CHILD)
	{
		pipeline_redirection(current, read_fd, pipe_end);
		options = ft_split(current->value, ' ');
		if (execution_builtins(current, options) == NO)
			execution_access(current, options);
		exit(get_minishell()->exit_nb);
	}
	waitpid(id, NULL, 0);
	close(pipe_end[1]);
	current = current->next;
	if (current != NULL)
		return (pipeline_fork(current, pipe_end[0]));
}

void	pipeline_redirection(t_node *current, int read_fd, int *pipe_end)
{
	if (current->fd_i != STDIN_FILENO)
	{
		dup2(current->fd_i, STDIN_FILENO);
		close(current->fd_i);
	}
	else
		dup2(read_fd, STDIN_FILENO);
	if (current->fd_o != STDOUT_FILENO)
	{
		dup2(current->fd_o, STDOUT_FILENO);
		close(current->fd_o);
	}
	else if (current->next != NULL)
		dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[0]);
	close(pipe_end[1]);
}