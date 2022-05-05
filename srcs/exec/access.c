/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:42:38 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/05 17:24:28 by tshimoda         ###   ########.fr       */
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
				//
				printf("FOUND PATHS\n");
				return (&(minishell->env[i])[6]);
			}
			else
			{
				//
				printf("PATH=\n");
				return (NULL);
			}
		}
		i++;	
	}
	return (NULL);
}

void execution_binary_cmd(t_node *current, int read_fd, char **options)
{
	pid_t id;
	int pipe_end[2]
	if (pipe(pipe_end) == FAIL)
		// message d'erreur

	// REDIRECTION INPUT
	if (current->fdI != STDIN_FILENO)
	{
		dup2(current->fdI, STDIN_FILENO);
		close(current->fdI); // celui d'une redirection
	}
	else if (read_fd != STDIN_FILENO)
	{
		dup2(read_fd, STDIN_FILENO);
		close(read_fd); // soit du infile ou bien celui du pipe_end[0]
	}

	// REDIRECTION OUTPUT : soit dans le stdout, soit dans une pipe ou soit dans un outfile finale.
	if (current->fdO != STDOUT_FILENO)
		dup2(current->fdO, STDOUT_FILENO);
	else if (current->next != NULL)
		dup2(pipe_end[1], STDOUT_FILENO);
		
	id = fork();
	if (id == FAIL)
		// erreur
	if (id == CHILD)
	{
		// inside the child process
		execution_access(options);
	}
	else
	{
		close(pipe_end[1]); // car le parent n'écrit pas dans le write_end a.k.a pipe_end[1]
		waitpid(id, NULL, 0);
	}
	if (current->next != NULL)
	{
		current = current->next;
		return (execution_binary_cmd(current, pipe_end[0]));
	}
}

// inside the child process
int	execution_access(char **options)
{
	t_minishell *minishell;
	char **path_table;

	// on essaie access si options[0] est un direct path
	minishell = get_minishell();
	// while loop ou non ???
	if (access(options[0], F_OK) == SUCCESS)
	{
		execve(options[0], options, minishell->env);
	}
	path_table = ft_split(get_path_value(minishell), ':');
	if (!path_table)
	{
		printf("NO PATH FOUND\n");
		// return une erreur ou on continue???
		// printf command not found du child process exit
	}
	// on essaie d'access avec tous les paths
	search_binary_file(path_table, options);
	ft_free_table(path_table);
}

int	search_binary_file(char **path_table, char **options)
{
	char *test_path;
	int i;

	i = 0;
	while(path_table[i] != NULL)
	{
		test_path = ft_strjoin_symbol(path_table[i], '/', options[0]);
		if (access(test_path, F_OK) == SUCCESS)
		{
			execve(test_path, options, get_minishell()->env);
		}
		free(test_path);
		i++;
	}
	// printfcommand not found);
	return (FAIL);
}
