/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:23 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/16 13:55:41 by tshimoda         ###   ########.fr       */
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

void	heredoc_preparation(t_node *current, char *safeword)
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
		heredoc_execution(current, pipe_end, safeword);
	}
}

void	heredoc_execution(t_node *current, int *pipe_end, char *safeword)
{
	char *heredoc_input;
	
	signal(SIGINT, &ctrl_c_heredoc);
	while (true)
	{
		heredoc_input = readline("> ");
		if (heredoc_input == CTRL_D)
			ctrl_d_heredoc_exit();
		if (ft_strcmp(heredoc_input, safeword) == SUCCESS)
		{
			close(pipe_end[0]);
			close(pipe_end[1]);
			break ;
		}
		ft_putendl_fd(heredoc_input, pipe_end[1]);
		free(heredoc_input);
	}

}

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

// les heredocs doivent etre dans un child process
// il faut une fonction signal pour le child qui s'intterompt dans un heredoc
// child process exit normally WIFEXITED AND WIFEXITEDSTATUS




/*
int    redir_heredoc(char *limiter, int fd, t_job *job)
{
	int        new_fd[2];
	pid_t    pid;
	int        wstatus;

	signal(SIGINT, nothing);
	pipe(new_fd);
	pid = fork();
	if (pid == 0)
		heredoc(limiter, new_fd, job);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	if (WIFEXITED(wstatus))
		g_msh.ret_exit = WEXITSTATUS(wstatus);
	dup2(new_fd[0], fd);
	close(new_fd[1]);
	close(new_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (1);
	return (0);
}
