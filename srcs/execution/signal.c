/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:38:55 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/04 11:57:24 by tshimoda         ###   ########.fr       */
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

void	ctrl_c_prompt(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	get_minishell()->exit_nb = SIG_CTRL_C;
}

// for a heredoc inside the child process
void	ctrl_c_heredoc(int signal)
{
	(void)signal;
	write(1, "  \n", 3);
	exit(SIG_CTRL_C);
}
// not sure about the exit nb

void	ctrl_d_exit(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_minishell();
	exit(get_minishell()->exit_nb);
}
// not sure about the exit nb

void	void_signal(int signal)
{
	(void)signal;
}

void	mute_signals(void)
{
	signal(SIGINT, &void_signal);
	signal(SIGQUIT, &void_signal);
}

void	set_signals(void)
{
	signal(SIGINT, &ctrl_c_prompt);
	signal(SIGQUIT, SIG_IGN);
}


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