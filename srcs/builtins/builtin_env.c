/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:05:56 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/20 11:19:47 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		env_var_is_key_only(char *option)
{
	int i;
	int equal;

	i = 0;
	equal = YES;
	while (option[i])
	{
		if (option[i] == '=')
		{
			equal = NO;
			break ;
		}
		i++;
	}
	return (equal);
}

void	builtin_env(char **options)
{
	// what should I do if someone puts an option ex. -LP
	if (*options != NULL && *options[0] != '-')
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(*options, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		get_minishell()->exit_nb = ERROR_127;
	}
	else
	{
		env_var_print();
		get_minishell()->exit_nb = SUCCESS;
	}
}
