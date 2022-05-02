/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:10:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/02 16:59:21 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
		minishell.user_input = NULL;
		minishell.options = NULL;
		minishell.head = NULL;
	}
	return (&minishell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char		**options;

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
		add_history(minishell->user_input);
		if (minishell->user_input == CTRL_D)
			ctrl_d_exit();

		// else if (ft_strcmp(minishell->user_input, "heredoc") == SUCCESS)
		// 	here_document("FIN");
			
		if (minishell->options != NULL)
			ft_free_table(minishell->options);
		options = ft_split(minishell->user_input, ' ');
		minishell->options = options;

		if (execution_builtins(options) == NO)
		{
			execution_access(options);
		}
	}
	return (0);
}

int	execution_access(char **options)
{
	t_minishell *minishell;
	char **path_table;
	int i;

	i = 0;

	// on essaie access si options[0] est un direct path
	minishell = get_minishell();
	path_table = ft_split(get_path_value(minishell), ':');
	// while loop ou non ???
	if (access(options[i], F_OK) == SUCCESS)
	{
		// pipe, fork, child execve
		// return ???
	}

	// on essaie access avec tous les paths
	if (!path_table)
	{
		printf("NO PATH FOUND\n");
		// return une erreur ou on continue???
	}
	// search_binary_file(path_table, cmd);
	
	ft_free_table(path_table);
}



int	search_binary_file(char **path_table, char *cmd)
{
	char *test_path;
	int i;

	i = 0;
	while(path_table[i] != NULL)
	{
		test_path = ft_strjoin_symbol(path_table[i], '/', cmd);
		if (access(test_path, F_OK) == SUCCESS)
			// execute fonction return(SUCCESS);
		free(test_path);
		i++;
	}
	return (FAIL);
}

void execution_binary_cmd(void)
{
	/*
	pid_t id;
	int pipe_end[2]
	if (pipe(pipe_end) == FAIL)
		// message d'erreur
	dup2(in_fd, 0);
	close(in_fd);

	if (pas d'autre redirection)
		dup2(out_fd, 1);
	else
		dup2(pipe_end[1], 1);

	id = fork();
	if (id == FAIL)
		// erreur
	if (id == CHILD)
		execve(binary_path, cmd+params, minishell->env)
	// PARENT
	close(pipe)end[1];
	waitpid(id, NULL, 0);

	*/
}