/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:23 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/05 13:18:18 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_preparation(t_node *current)
{
	pid_t	id;
	int		pipe_end[2];
	int		wstatus;

	signal(SIGINT, &void_signal);
	if (pipe(pipe_end) == FAIL)
		ft_putendl_fd("Error at heredoc pipe", STDERR_FILENO);
	id = fork();
	if (id == FAIL)
		ft_putendl_fd("Error at heredoc fork", STDERR_FILENO);
	if (id == CHILD)
		heredoc_execution(current, pipe_end);
	waitpid(id, &wstatus, 0);
	heredoc_after_execution(current, wstatus);
	dup2(pipe_end[0], current->fd_i);
	close(pipe_end[0]);
	close(pipe_end[1]);
}

void	heredoc_after_execution(t_node *current, int wstatus)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == SIG_CTRL_C)
	{
		current->flag = YES;
		current->type = 'e';
		minishell->exit_nb = ERROR_1;
		minishell->is_heredoc = YES;
	}
	else if (WIFEXITED(wstatus))
	{
		minishell->exit_nb = WEXITSTATUS(wstatus);
		minishell->is_heredoc = YES;
	}
}

void	heredoc_execution(t_node *current, int *pipe_end)
{
	char		*heredoc_input;
	char		*tmp;

	signal(SIGINT, &ctrl_c_heredoc);
	while (true)
	{
		heredoc_input = readline("> ");
		if (heredoc_input == CTRL_D)
		{
			ft_close_pipe(pipe_end);
			free(heredoc_input);
			ctrl_d_heredoc_exit();
		}
		tmp = get_var_heredoc(heredoc_input, 1, 0, 0);
		free(heredoc_input);
		if (ft_is_matching_strings(tmp, current->eof) == SUCCESS)
			break ;
		ft_putendl_fd(tmp, pipe_end[1]);
		free(tmp);
		tmp = NULL;
	}
	ft_close_pipe(pipe_end);
	if (tmp)
		free(tmp);
	exit(SUCCESS);
}
		//heredoc_input = get_var(current, heredoc_input, 1, -1);

void	heredoc_main(t_node *current, char **file)
{
	current->type = 'h';
	if (current->eof)
	{
		free(current->eof);
		current->eof = NULL;
	}
	current->eof = ft_strdup(*file);
	current->fd_i = dup(STDIN_FILENO);
	heredoc_preparation(current);
	free(*file);
	*file = NULL;
}
