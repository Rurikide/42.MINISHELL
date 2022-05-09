/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:42:38 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/09 17:50:20 by tshimoda         ###   ########.fr       */
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


// RETURNS a BOOLEAN INT but ALSO perform the builtin is there is a match!!!
int	execution_builtins(t_node *current, char **options)
{
	int is_builtin;
	
	is_builtin = YES;
	if (ft_is_a_match("echo", options[0]) == YES)
		builtin_echo(current, &options[1]);
	else if (ft_is_a_match("cd", options[0]) == YES)
		builtin_cd(&options[1]);
	else if (ft_is_a_match("pwd", options[0]) == YES)
		builtin_pwd(current, &options[1]);
	else if (ft_is_a_match("export", options[0]) == YES)
		builtin_export(current, &options[1]);
	else if (ft_is_a_match("unset", options[0]) == YES)
		builtin_unset(current, &options[1]);
	else if (ft_is_a_match("env", options[0]) == YES)
		builtin_env(current, &options[1]);
	else if (ft_is_a_match("exit", options[0]) == YES)
		builtin_exit(current, &options[1]);
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


// prepare PIPE, FD, puis FORK. 
void execution_binary_cmd(t_node *current, int read_fd, char **options)
{
	pid_t id;
	int pipe_end[2];
	if (pipe(pipe_end) == FAIL)
		printf("PIPE FAILED\n");
		
	// REDIRECTION INPUT
	if (current->fd_i != STDIN_FILENO)
	{
		dup2(current->fd_i, STDIN_FILENO);
		close(current->fd_i); // celui d'une redirection
	}
	else if (read_fd != STDIN_FILENO)
	{
		dup2(read_fd, STDIN_FILENO);
		close(read_fd); // soit du infile ou bien celui du pipe_end[0]
	}

	// REDIRECTION OUTPUT : soit dans le stdout, soit dans une pipe ou soit dans un outfile finale.
	if (current->fd_o != STDOUT_FILENO)
	{
		dup2(current->fd_o, STDOUT_FILENO);
	}
	else if (current->next != NULL)
	{
		dup2(pipe_end[1], STDOUT_FILENO);
	}
	id = fork();
	
	if (id == FAIL)
	{
		//
		printf("forked == fail\n");
	}

	
	if (id == CHILD)
	{
		// inside the child process
		execution_access(options);
	}
	close(pipe_end[1]); // car le parent n'écrit pas dans le write_end a.k.a pipe_end[1]
	waitpid(id, NULL, 0);
	if (current->next != NULL)
	{
		current = current->next;
		return (execution_binary_cmd(current, pipe_end[0], options));
	}
}

// inside the child process. called from execution_binary_cmd
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
	// on essaie d'access avec tous les paths; EXECVE
	search_binary_file(path_table, options);
	ft_free_table(path_table);

	//
	return (0);
}

// EXCEVE 
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
