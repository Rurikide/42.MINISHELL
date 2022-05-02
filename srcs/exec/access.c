/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:42:38 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/02 14:40:11 by tshimoda         ###   ########.fr       */
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

// void	execution_access(void)
// {
// 	t_minishell *minishell;
// 	char **bins;

// 	minishell = get_minishell();

// 	int	i;

// 	i = 1;
// 	bins = ft_split(get_path_value(minishell), ':');
// 	if (input->bins == NULL)
// 	{
// 		ft_printf("Error path variable is NULL\n");
// 		ft_free_table(input->bins);
// 		free(input->cmd);
// 		exit(EXIT_FAILURE);
// 	}
// 	while (input->argv[i] && input->argv[i + 1])
// 	{
// 		input->cmd[i].param = ft_split(input->argv[i], ' ');
// 		if (input->cmd[i].param == NULL)
// 			ft_perror_cmd_free(input, i, "Error split cmd");
// 		if (ft_is_valid_command(input, i, input->cmd[i].param[0]) == FAIL)
// 		{
// 			ft_printf("cmd #%d is invalid.\n", i);
// 			ft_perror_cmd_free(input, i, "Error parse cmd");
// 		}
// 		i++;
// 	}
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


// // access return 0 on success and -1 on fail
// int	execution_access(char **options)
// {	
// 	char **path_table;

// 	if (access(options, F_OK)  == SUCCESS)
// 	{
// 			execution_binary_cmd(options);
// 			// return ???
// 	}
// 	path_table = ft_split(get_path_value(get_minishell()), ':');
// 	if (path_table == NULL)
// 		//	s'il n'y a pas de path 
	
	
// }