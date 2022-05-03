/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:23 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/03 16:08:15 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

typedef struct s_hdinput
{
	struct	s_hdinput	*prev;
	struct	s_hdinput	*next;
	char	**hd_table;
}	t_hdinput;

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


//void	here_document(t_node *current, char *safeword)
void	here_document(char *safeword)
{
	// mute signals; for both PARENT and CHILD

	/*  pid_t here_id;
		here_id = fork();
		
		if (here_id == CHILD)
		{
			signal(SIGINT, &ctrl_c_heredoc); //signal pour le child process seulement
			char *hd_input;
			char *cmd;
			
			cmd = "cat";
			
			hd_input = readline("> ");
			if (ft_strcmp(hd_input, safeword) == SUCCESS)
				return ;
			while (ft_strcmp(hd_input, safeword) != SUCCESS)
			{
				//current->value = ft_strjoin_symbol(current->value, '\n', hd_input);
				cmd = ft_strjoin_symbol(cmd, '\n', hd_input);
				hd_input = readline("> ");
			}
			free(current_node->value);
			current->node->value = ft_strdup(cmd);
			exit status du child;
		}
		else // PARENT
		{
			waitpid(here_id, NULL, 0);
		}
		set_signals();
	*/
}

// les heredocs doivent etre dans un child process
// il faut une fonction signal pour le child qui s'intterompt dans un heredoc
// child process exit normally WIFEXITED AND WIFEXITEDSTATUS