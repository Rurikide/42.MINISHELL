/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:40:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/05 13:31:18 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_main(t_node *current)
{
	char	**options;
	int		i;

	i = -1;
	options = NULL;
	options = sp_split(current->value, ' ', 0, 0);
	while (options[++i])
	{
		if (ft_is_present('\'', options[i]) || ft_is_present('"', options[i]))
			options[i] = ms_strip(options[i], 0, 0);
	}
	if (current->next == NULL && is_a_builtin(options) == YES)
	{
		one_builtin_redirection(current, options);
		if (options != NULL)
			ft_free_table(options);
	}
	else if (current != NULL)
	{
		if (options != NULL)
			ft_free_table(options);
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
	int		pipe_end[2];
	int		wstatus;
	pid_t	id;

	while (current->type == 'e')
		current = current->next;
	pipe(pipe_end);
	id = fork();
	if (id == FAIL)
		ft_putstr_fd("Error at fork()\n", STDERR_FILENO);
	mute_signals();
	if (id == CHILD)
		pipeline_child_process(current, read_fd, pipe_end);
	waitpid(id, &wstatus, 0);
	set_signals();
	if (get_minishell()->is_heredoc == NO)
		set_exit_nb(wstatus);
	else
		get_minishell()->is_heredoc = NO;
	close(pipe_end[1]);
	if (current->next == NULL)
		close(pipe_end[0]);
	current = current->next;
	if (current != NULL)
		return (pipeline_fork(current, pipe_end[0]));
}

void	pipeline_child_process(t_node *current, int read_fd, int *pipe_end)
{
	char	**options;
	int		i;

	i = -1;
	pipeline_redirection(current, read_fd, pipe_end);
	options = sp_split(current->value, ' ', 0, 0);
	while (options[++i])
	{
		if (ft_is_present('\'', options[i]) || ft_is_present('"', options[i]))
			options[i] = ms_strip(options[i], 0, 0);
	}
	if (execution_builtins(options) == NO)
		execution_access(get_minishell(), options);
	ft_free_table(options);
	free_minishell();
	exit(get_minishell()->exit_nb);
}

void	pipeline_redirection(t_node *current, int read_fd, int *pipe_end)
{
	if (current->fd_i != STDIN_FILENO)
	{
		dup2(current->fd_i, STDIN_FILENO);
		close(current->fd_i);
	}
	else
	{
		if (read_fd != STDIN_FILENO)
		{
			dup2(read_fd, STDIN_FILENO);
			close(read_fd);
		}
	}	
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
