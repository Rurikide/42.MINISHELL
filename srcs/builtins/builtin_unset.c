/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:10:52 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/18 13:57:02 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
// UNSET deletes an existing env var
// search the environment for the KEY of a KEY=VALUE
// CANNOT UNSET a key ending by an '=' sush as VAR1=    must be VAR1
// POSSIBLE TO UNSET multiple var at the same time. 
// UNSET ALONE DOEST NOTHING SPECIAL

// ALEX if key == _3\allo  REMOVE THE BACK SLASH

t_answer	is_only_key_identifier(char *option)
{
	int	i;

	i = 1;
	if (!ft_isalpha(option[0]) && option[0] != '_')
		return (NO);
	while (option[i] != '\0')
	{
		if (!ft_isalnum(option[i]) && option[i] == '=')
			return (NO);
		i++;
	}
	return (YES);
}

void	builtin_unset(char **options)
{
	int		i;
	int		env_index;

	i = 0;
	while (options[i] != NULL)
	{
		if (is_only_key_identifier(options[i]) == NO)
		{
			printf("unset: %s: not a valid identifier\n", options[i]);
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
