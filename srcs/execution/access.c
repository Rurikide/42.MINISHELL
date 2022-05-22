/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:42:38 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/21 22:26:31 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_free_table(options);
		if (env_var_matching_key("PATH") == FAIL)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(msg_err, STDERR_FILENO);
			exit(126);
		}
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	path_table = ft_split(get_path_value(minishell), ':');
	if (!path_table)
		env_var_missing_path(options);
	search_binary_file(path_table, options, 0);
}

void	env_var_missing_path(char **options)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(*options, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	ft_free_table(options);
	exit(ERROR_127);
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
			ft_free_table(options);
			exit(ERROR_127);
		}
		free(test_path);
		i++;
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(*options, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	ft_free_table(options);
	exit(ERROR_127);
}
