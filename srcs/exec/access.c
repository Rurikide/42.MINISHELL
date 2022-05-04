/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:42:38 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/04 12:47:09 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// void mise_en_abyme(char **options)
// {
// 	pid_t process_id;

// 	process_id = fork();

// 	if (process_id == SUCCESS)
// 	{
// 		execve(*options, options, get_minishell()->env);
// 		printf("hello from child process\n");
// 	}
// 	else 
// 		waitpid(process_id, NULL, 0);
// }

int	execution_builtins(char **options)
{
	int is_builtin;

	is_builtin = YES;
	if (ft_is_a_match("echo", options[0]) == YES)
		builtin_echo(&options[1]);
	else if (ft_is_a_match("cd", options[0]) == YES)
		builtin_cd(&options[1]);
	else if (ft_is_a_match("pwd", options[0]) == YES)
		builtin_pwd(&options[1]);
	else if (ft_is_a_match("export", options[0]) == YES)
		builtin_export(&options[1]);
	else if (ft_is_a_match("unset", options[0]) == YES)
		builtin_unset(&options[1]);
	else if (ft_is_a_match("env", options[0]) == YES)
		builtin_env(&options[1]);
	else if (ft_is_a_match("exit", options[0]) == YES)
		builtin_exit(&options[1]);
	else
		is_builtin = NO;
	return (is_builtin);
}

// returns the value of PATH or NULL is PATH is unset
char	*get_path_value(t_minishell *minishell)
{
	int i;

	i = 0;
	if (minishell->env[i] == NULL)
		return (NULL);
	while (minishell->env[i] != NULL)
	{
		if (ft_strncmp(minishell->env[i], "PATH=", 5) == SUCCESS)
		{
			if (minishell->env[i][6] != '\0')
			{
				printf("FOUND PATHS\n");
				return (&(minishell->env[i])[6]);
			}
			else
			{
				printf("PATH=\n");
				return (NULL);
			}
		}
		i++;	
	}
	return (NULL);
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
	search_binary_file(path_table, cmd);
	
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
	/* il faut que je pipe et fork avant???
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