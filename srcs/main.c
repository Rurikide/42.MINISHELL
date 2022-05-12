/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:10:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/12 14:00:43 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incls/builtins.h"

t_minishell	*get_minishell(void)
{
	static t_minishell	minishell;

	if (minishell.init != 1)
	{
		minishell.init = 1;
		minishell.shlvl = 1;
		minishell.env = NULL;
		minishell.env_size = 0;
		minishell.exit_nb = 0;
		minishell.bu_fd_in = dup(0);
		minishell.bu_fd_out = dup(1);
		minishell.in_pipeline = NO;
		minishell.user_input = NULL;
		minishell.options = NULL;
		minishell.head = NULL;
	}
	return (&minishell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
//	char		**options;

	(void)argc;
	(void)argv;
	init_env(env);
	minishell = get_minishell();
	set_signals();

	while (true)
	{
		if (minishell->user_input != NULL)
			free(minishell->user_input);
		minishell->user_input = readline("minishell> ");
		if (minishell->user_input == CTRL_D)
			ctrl_d_exit();
		add_history(minishell->user_input);
		if (minishell->options != NULL)
			ft_free_table(minishell->options);
	//	options = ft_split(minishell->user_input, ' ');
	//	minishell->options = options;
		ms_parsing();
		t_node *current;

		current = minishell->head;
		// pipeline_open(minishell);
		if (current->next == NULL && is_a_builtin(ft_split(current->value, ' ')) == YES)
		{
			printf("Condition #1\n");

			if (current->fd_i != 0)
			{
				dup2(current->fd_i, 0);
				close(current->fd_i);
			}

			if (current->fd_o != 1)
			{
				dup2(current->fd_o, 1);
				close(current->fd_o);
			}
			execution_builtins(current, (ft_split(current->value, ' ')));
		}
		// sois un binary cmd seul OU BIEN pipeline de plusieurs nodes
		else if(current != NULL)
		{
			printf("Condition #2\n");
			pipeline_fork(current, 0);
		}
	}
	return (0);
}


void	pipeline_fork(t_node *current, int read_fd)
{
	static int node;
	int pipe_end[2];
	pid_t id;

	node++;
	printf("---node #%d---\n", node);
	pipe(pipe_end);
	if (pipe(pipe_end) == FAIL)
		printf("error pipe didn't work\n");
	
	printf("current->value is %s\n", current->value);
	// REDIRECTION INPUT 
	if (current->fd_i != STDIN_FILENO)
	{
		dup2(current->fd_i, STDIN_FILENO);
		close(current->fd_i);
	}
	else
	{
		dup2(read_fd, STDIN_FILENO);
	}

	// REDIRECTION OUTPUT 
	if (current->fd_o != STDOUT_FILENO)
	{
		dup2(current->fd_o, STDOUT_FILENO);
		close(current->fd_o);
	}
	else if (current->next != NULL)
	{
		dup2(pipe_end[1], STDOUT_FILENO);
	}
	else
		dup2(get_minishell()->bu_fd_out, STDOUT_FILENO);

	
	id = fork();
	if (id == FAIL)
		printf("FORK DIDNT WORK\n");
	
	if (id == CHILD)
	{
		if (execution_builtins(current, ft_split(current->value, ' ')) == NO)
		{
			printf("\033[1;34mAFTER EXECUTION BUILTIN\033[0m\n");
			execution_access(current, ft_split(current->value, ' '));
		}
	}
	waitpid(id, NULL, 0);
	close(pipe_end[1]);
	//dup2(get_minishell()->bu_fd_in, STDIN_FILENO);
	//dup2(get_minishell()->bu_fd_out, STDOUT_FILENO);
	current = current->next;
	if (current != NULL)
		return (pipeline_fork(current, pipe_end[0]));
}







	// if (current->fd_i == STDIN_FILENO)
	// {
	// 	dup2(fd_i, STDIN_FILENO);
	// 	close(fd_i);
	// }
	// else
	// {
	// 	dup2(current->fd_i, STDIN_FILENO);
	// 	close(current->fd_i);
	// }

	// if (current->fd_o == STDOUT_FILENO)
	// {
	// 	dup2(pipe_end[1], STDOUT_FILENO);
	// }
	// else
	// {
	// 	dup2(current->fd_o, STDOUT_FILENO);
	// 	close(current->fd_o);
	// }