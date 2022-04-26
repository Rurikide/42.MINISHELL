/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:38:55 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/26 16:14:48 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// CTRL-C clear the user input CTRL-D close one shell CTRL-backslash

//      SIGINT  (2)     P1990      Term    Interrupt from keyboard
//		SIGQUIT backslash
//   SIGKILL (9)

void	mute_signal(int signal)
{
	(void)signal;
	//dans un fork, pour éviter que le ctrl-c et ctrl-\ se fasse en double par le parent et child process
}

void	ctrl_c_handler(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
//	ft_putstr_fd("\r\r\r", STDOUT_FILENO);
//	ft_putstr_fd("  \n", STDERR_FILENO);
	
	// Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline. 
	rl_on_new_line();

	//Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible
	rl_replace_line("", 0);

	//Change what's displayed on the screen to reflect the current contents of rl_line_buffer. 
	rl_redisplay();
	
	get_minishell()->exit_nb = 130; // not sure about that
}

// control-d is actually not a signal, but a user input  ^C to remove???
void		ctrl_d_exit(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_minishell();
	exit(get_minishell()->exit_nb);
}

void set_signals(void)
{
	signal(SIGINT, &ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
}
