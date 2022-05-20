/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:23 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/20 11:30:59 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_preparation(t_node *current)
{
	pid_t	id;
	int		pipe_end[2];
	int		wstatus;

	mute_signals();
	if (pipe(pipe_end) == FAIL)
		ft_putendl_fd("Error at heredoc pipe", STDERR_FILENO);
	id = fork();
	if (id == FAIL)
		ft_putendl_fd("Error at heredoc fork", STDERR_FILENO);
	if (id == CHILD)
	{
		heredoc_execution(current, pipe_end);
	}
	waitpid(id, &wstatus, 0);
	set_signals();
	if (WIFEXITED(wstatus))
		get_minishell()->exit_nb = WEXITSTATUS(wstatus);
	dup2(pipe_end[0], current->fd_i);
	if (pipe_end[0] != STDIN_FILENO)
		close(pipe_end[0]);
	if (pipe_end[0] != STDOUT_FILENO)
		close(pipe_end[1]);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIG_CTRL_C)
		get_minishell()->exit_nb = ERROR_1;
}

void	heredoc_execution(t_node *current, int *pipe_end)
{
	char	*heredoc_input;

	signal(SIGINT, &ctrl_c_heredoc);
	while (true)
	{
		heredoc_input = readline("> ");
		if (heredoc_input == CTRL_D)
		{
			free(heredoc_input);
			ctrl_d_heredoc_exit();
		}
		if (ft_is_matching_strings(heredoc_input, current->eof) == SUCCESS)
		{
			close(pipe_end[1]);
			close(pipe_end[0]);
			break ;
		}
		ft_putendl_fd(heredoc_input, pipe_end[1]);
		free(heredoc_input);
	}
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
