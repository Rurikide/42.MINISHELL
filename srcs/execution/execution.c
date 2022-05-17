/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:40:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/17 16:17:48 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	execution_main(t_node *current)
{
	char	**options;
	int		i;

	i = 0;
	options = ft_split(current->value, ' ');
	if (current->next == NULL && is_a_builtin(options) == YES)
	{
		one_builtin_redirection(current, options);
		if (options != NULL)
			ft_free_table(options);
	}
	else if (current != NULL)
	{
		pipeline_fork(current, current->fd_i);
	}
}

void	one_builtin_redirection(t_node *current, char **options)
{
	int	bu_fd_in;
	int	bu_fd_out;

	bu_fd_in = dup(STDIN_FILENO);
	bu_fd_out = dup(STDOUT_FILENO);
	if (current->fd_i != STDIN_FILENO)
	{
		dup2(current->fd_i, STDIN_FILENO);
		close(current->fd_i);
	}
	if (current->fd_o != STDOUT_FILENO)
	{
		dup2(current->fd_o, STDOUT_FILENO);
		close(current->fd_o);
	}
	execution_builtins(options);
	dup2(bu_fd_in, STDIN_FILENO);
	dup2(bu_fd_out, STDOUT_FILENO);
	close(bu_fd_in);
	close(bu_fd_out);
}

void	pipeline_fork(t_node *current, int read_fd)
{
	char	**options;
	int		pipe_end[2];
	int		wstatus;
	pid_t	id;

	if (pipe(pipe_end) == FAIL)
		ft_putstr_fd("Error at pipe()\n", STDERR_FILENO);
	id = fork();
	if (id == FAIL)
		ft_putstr_fd("Error at fork()\n", STDERR_FILENO);
	if (id == CHILD)
	{
		pipeline_redirection(current, read_fd, pipe_end);
		options = ft_split(current->value, ' ');
		if (execution_builtins(options) == NO)
			execution_access(get_minishell(), options);
		exit(get_minishell()->exit_nb);
	}
	waitpid(id, &wstatus, 0);
	close(pipe_end[1]);
	if (WIFEXITED(wstatus))
		get_minishell()->exit_nb = WEXITSTATUS(wstatus);
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
