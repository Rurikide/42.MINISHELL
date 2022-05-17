/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:10:52 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/17 15:10:52 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_answer	is_only_key_identifier(char *option)
{
	int	i;

	i = 1;
	if (!ft_isalpha(option[0]) && option[0] != '_')
		return (NO);
	while (option[i] != '\0')
	{
		if (!ft_isalnum(option[i]) && option[i] != '_')
			return (NO);
		i++;
	}
	return (YES);
}

void	builtin_unset(char **options, int i)
{
	int	env_index;

	get_minishell()->exit_nb = SUCCESS;
	while (options[i] != NULL)
	{
		if (is_only_key_identifier(options[i]) == NO)
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(options[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			get_minishell()->exit_nb = ERROR_1;
		}
		else
		{
			env_index = env_var_matching_key(options[i]);
			if (env_index != FAIL)
			{
				if (ft_strncmp(options[i], "SHLVL", 5) == SUCCESS)
					env_var_update("SHLVL", "1");
				else
					env_var_del(env_index);
			}
		}
		i++;
	}
}
