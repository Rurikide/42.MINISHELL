/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:38:55 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/21 17:34:57 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

// control_c PARENT PROCESS
void	ctrl_c_prompt(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(STDERR_FILENO, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	get_minishell()->exit_nb = ERROR_1;
}

// for a heredoc inside the child process
// zsh and updated version of bash exit_code is 130
// control_c CHILD PROCESS
void	ctrl_c_heredoc(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "  \n", 3);
	get_minishell()->exit_nb = ERROR_1;
	exit(SIG_CTRL_C);
}

// control_d PARENT PROCESS
void	ctrl_d_exit(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_minishell();
	exit(get_minishell()->exit_nb);
}

// control_d CHILD PROCESS
// On BASH ctrl-D inside a heredoc does : > bash prompt
void	ctrl_d_heredoc_exit(void)
{
	free_minishell();
	exit(get_minishell()->exit_nb);
}

void	void_signal(int signal)
{
	(void)signal;
}
