/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:42:38 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/12 13:47:53 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_a_builtin(char **options)
{
	int is_builtin;

	if (ft_is_a_match("echo", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("cd", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("pwd", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("export", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("unset", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("env", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("exit", options[0]) == YES)
		is_builtin = YES;
	else
		is_builtin = NO;
	//ft_free_table(options);
	return (is_builtin);
}

int	execution_builtins(t_node *current, char **options)
{
	int is_builtin;

	//
	printf("\033[1;32mINSIDE EXECUTION BUILTIN\033[0m\n");
	//
	
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
				//printf("FOUND PATHS\n");
				//
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

// inside the child process. called from execution_binary_cmd
int	execution_access(t_node *current, char **options)
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
		// cat écrit permission denied 
		ft_putstr_fd("minishell: ", current->fd_o);
		ft_putstr_fd(*options, current->fd_o);
		ft_putstr_fd(": No such file or directory\n", current->fd_o);
		printf("NO PATH FOUND from execution_access\n");
		// return une erreur ou on continue???
		// printf command not found du child process exit
	}
	// on essaie d'access avec tous les paths; EXECVE
	search_binary_file(path_table, options);
	//ft_free_table(path_table);

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
			// strerror(errno);
			// get_minishell()->exit_nb = 127;
			// exit(127);
		}
		free(test_path);
		i++;
	}
	// NOT SURE ABOUT THAT(
	printf("--- No such file or directory found\n");
	get_minishell()->exit_nb = 127;
	exit(127);
	// que faire lorsqu'il le child ne trouve pas de path???
	return (FAIL);
}
