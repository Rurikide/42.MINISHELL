/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:05:56 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/14 13:39:48 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_var_print(void)
{

	t_minishell	*minishell;
	int			i;
	i = 0;
	minishell = get_minishell();
	while (minishell->env[i] != NULL)
	{
		if (env_var_is_key_only(minishell->env[i]) == NO)
			ft_putendl_fd(minishell->env[i], STDOUT_FILENO);
		i++;
	}
}

void	builtin_env(char **options)
{
	if (*options != NULL && *options[0] != '-')
	{
		ft_putstr_fd("env: ",  STDOUT_FILENO);
		ft_putstr_fd(*options,  STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n",  STDOUT_FILENO);
		get_minishell()->exit_nb = ERROR_127;
	}
	else
	{
		env_var_print();
		get_minishell()->exit_nb = SUCCESS;
	}
}
