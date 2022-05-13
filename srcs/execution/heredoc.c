/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:23 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/13 17:21:09 by tshimoda         ###   ########.fr       */
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

void	here_document(t_node *current, char *safeword)
{
		pid_t here_id;
		char *hd_input;
		char *cmd;
		
		// IL FAUT FAIRE UN PIPE le child process a sa propre node et il faut qu'il partage ses infos avec le parent
		cmd = "cat";
		mute_signals();
		here_id = fork();
		if (here_id == CHILD)
		{
			signal(SIGINT, &ctrl_c_heredoc);
			hd_input = readline("> ");
			if (hd_input == CTRL_D)
				// > bash response
			if (ft_strcmp(hd_input, safeword) == SUCCESS)
				return ;
			// strategie rempli value de tous les user inputs séparé par des newline
			while (ft_strcmp(hd_input, safeword) != SUCCESS)
			{
				//current->value = ft_strjoin_symbol(current->value, '\n', hd_input);
				cmd = ft_strjoin_symbol(cmd, '\n', hd_input);
				hd_input = readline("> ");
				// VERIFIER LE CTRL-D DANS LE HEREDOC
				if (hd_input == CTRL_D)
					ctrl_d_exit();
				// > bash response
				// est-ce que je dois faire quelquechose pour le readline? utilise rl_on_new_line() rl_replace_line() rl_redisplay()
			}
			free(current->value);
			current->value = ft_strdup(cmd);
			// exit status du child;
		}
		else // PARENT
		{
			waitpid(here_id, NULL, 0);
		}
		set_signals();
}

// les heredocs doivent etre dans un child process
// il faut une fonction signal pour le child qui s'intterompt dans un heredoc
// child process exit normally WIFEXITED AND WIFEXITEDSTATUS