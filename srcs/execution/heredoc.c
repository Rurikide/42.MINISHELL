/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:23 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/17 11:47:49 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
	rl_on_new_line();
	Tell the update routines that we have moved onto a new (empty) line, 
	usually after ouputting a newline. 
	
	rl_replace_line("", 0);
	Replace the contents of rl_line_buffer with text. 
	The point and mark are preserved, if possible
	
	rl_redisplay();
	Change what's displayed on the screen to reflect the current contents of 
	rl_line_buffer. 
*/

/*

WIFEXITED(status)
	returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main(). 
WEXITSTATUS(status)
	returns the exit status of the child. This consists of the least significant 8 bits of the status argument that the child specified in a call to exit(3) or _exit(2) or as the argument for a return statement in main(). This macro should only be employed if WIFEXITED returned true. 
WIFSIGNALED(status)
	returns true if the child process was terminated by a signal. 

wait() and waitpid()

The wait() system call suspends execution of the calling process until one of its children terminates. The call wait(&status) is equivalent to:

waitpid(-1, &status, 0);

*/

// Fonction après avoir trouver un '<<'
// Comment le parsing gère un et plusieurs heredocs???

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
	char *heredoc_input;
	
	signal(SIGINT, &ctrl_c_heredoc);
	while (true)
	{
		heredoc_input = readline("> ");
		if (heredoc_input == CTRL_D)
			ctrl_d_heredoc_exit();
		if (matching_strings(heredoc_input, current->eof) == SUCCESS)
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

int	matching_strings(char *s1, char *s2)
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

// OTHER VERSION
// void	here_document(t_node *current, char *safeword)
// {
// 		pid_t here_id;
// 		char *hd_input;
// 		char *cmd;
		
// 		cmd = "cat";
// 		mute_signals();
// 		here_id = fork();
// 		if (here_id == CHILD)
// 		{
// 			signal(SIGINT, &ctrl_c_heredoc);
// 			hd_input = readline("> ");
// 			if (hd_input == CTRL_D)
// 				// > bash response
// 			if (ft_strcmp(hd_input, safeword) == SUCCESS)
// 				return ;
// 			// strategie rempli value de tous les user inputs séparé par des newline
// 			while (ft_strcmp(hd_input, safeword) != SUCCESS)
// 			{
// 				//current->value = ft_strjoin_symbol(current->value, '\n', hd_input);
// 				cmd = ft_strjoin_symbol(cmd, '\n', hd_input);
// 				hd_input = readline("> ");
// 				// VERIFIER LE CTRL-D DANS LE HEREDOC
// 				if (hd_input == CTRL_D)
// 					ctrl_d_exit();
// 				// > bash response
// 			}
// 			free(current->value);
// 			current->value = ft_strdup(cmd);
// 			// exit status du child;
// 		}
// 		waitpid(here_id, NULL, 0);
// 		set_signals();
// }
