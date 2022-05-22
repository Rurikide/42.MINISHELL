/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:23 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/22 11:52:40 by tshimoda         ###   ########.fr       */
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
		tmp = get_var(heredoc_input, 1, -1);
		if (heredoc_input == CTRL_D)
		{
			close(pipe_end[0]);
			close(pipe_end[1]);
			free(heredoc_input);
			ctrl_d_heredoc_exit();
		}
		if (ft_is_matching_strings(heredoc_input, current->eof) == SUCCESS)
			break ;
		ft_putendl_fd(tmp, pipe_end[1]);
		free(tmp);
		free(heredoc_input);
	}
	close(pipe_end[0]);
	close(pipe_end[1]);
	free(heredoc_input);
	exit(SUCCESS);
}

int	ft_is_matching_strings(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1) - 1;
	s2_len = ft_strlen(s2) - 1;
	if (s1_len != s2_len)
		return (FAIL);
	while (s1[s1_len] && s2[s2_len])
	{
		if (s1[s1_len] != s2[s2_len])
			return (FAIL);
		s1_len--;
		s2_len--;
	}
	return (SUCCESS);
}
