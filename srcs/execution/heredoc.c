/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:23 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/17 15:27:51 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	heredoc_preparation(t_node *current)
{
	pid_t	id;
	int		pipe_end[2];
	int		wstatus;

	if (pipe(pipe_end) == FAIL)
		ft_putendl_fd("Error at heredoc pipe", STDERR_FILENO);
	mute_signals();
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
	close(pipe_end[0]);
	close(pipe_end[1]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == SIG_CTRL_C)
		get_minishell()->exit_nb = ERROR_1;
	else
		get_minishell()->exit_nb = SUCCESS;
}

void	heredoc_execution(t_node *current, int *pipe_end)
{
	char	*heredoc_input;

	signal(SIGINT, &ctrl_c_heredoc);
	while (true)
	{
		heredoc_input = readline("> ");
		if (heredoc_input == CTRL_D)
			ctrl_d_heredoc_exit();
		if (ft_is_matching_strings(heredoc_input, current->eof) == SUCCESS)
		{
			dup2(pipe_end[1], current->fd_i);
			close(pipe_end[1]);
			close(pipe_end[0]);
			break ;
		}
		ft_putendl_fd(heredoc_input, pipe_end[1]);
		free(heredoc_input);
	}
	get_minishell()->exit_nb = SUCCESS;
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
