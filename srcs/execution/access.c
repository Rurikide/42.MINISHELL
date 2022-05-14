/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:42:38 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/14 13:30:53 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_a_builtin(char **options)
{
	int	is_builtin;

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
	return (is_builtin);
}
	//ft_free_table(options);

int	execution_builtins(char **options)
{
	int	is_builtin;

	is_builtin = YES;
	if (ft_is_a_match("echo", options[0]) == YES)
		builtin_echo(&options[1], 0);
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

// returns the value of PATH; returns NULL if PATH is unset
char	*get_path_value(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->env[i] == NULL)
		return (NULL);
	while (minishell->env[i] != NULL)
	{
		if (ft_strncmp(minishell->env[i], "PATH=", 5) == SUCCESS)
		{
			if (minishell->env[i][6] != '\0')
				return (&(minishell->env[i])[6]);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

void	execution_access(t_minishell *minishell, char **options)
{
	char		**path_table;
	char		*msg_err;

	if (access(options[0], F_OK) == SUCCESS)
	{
		execve(options[0], options, minishell->env);
		msg_err = strerror(errno);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(*options, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg_err, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		minishell->exit_nb = 126;
		exit(126);
	}
	path_table = ft_split(get_path_value(minishell), ':');
	if (!path_table)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(*options, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	search_binary_file(path_table, options, 0);
}
// ft_free_table(path_table);

void	search_binary_file(char **path_table, char **options, int i)
{
	char	*test_path;
	char	*msg_err;

	while (path_table[i] != NULL)
	{
		test_path = ft_strjoin_symbol(path_table[i], '/', options[0]);
		if (access(test_path, F_OK) == SUCCESS)
		{
			execve(test_path, options, get_minishell()->env);
			msg_err = strerror(errno);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(*options, STDERR_FILENO);
			ft_putstr_fd(msg_err, STDERR_FILENO);
			get_minishell()->exit_nb = 126;
			exit(126);
		}
		free(test_path);
		i++;
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(*options, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	get_minishell()->exit_nb = 127;
	exit(127);
}
