/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:10:52 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/13 15:40:35 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// UNSET deletes an existing env var
// search the environment for the KEY of a KEY=VALUE
// CANNOT UNSET a key ending by an '=' sush as VAR1=    must be VAR1
// POSSIBLE TO UNSET multiple var at the same time. 

t_answer is_only_key_identifier(char *option)
{
	int i;

	i = 1;
	if (!ft_isalpha(option[0]) && option[0] != '_')
		return (NO);
	while(option[i] != '\0')
	{
		if (option[i] == '=')
			return (NO);
		i++;
	}
	return (YES);
}

void	builtin_unset(char **options)
{
	int i;
	int len;
	int env_index;

	i = 0;
	while (options[i] != '\0')
	{
		// search if its a valid key
		if (is_only_key_identifier(options[i]) == NO)
		{
			printf("unset: %s: not a valid identifier\n", options[i]);
		}
		else
		{
			// if its a valid key. search for the index in the char **env
			// if == FAIL means the ENV VAR doesnt exist, do nothing
			env_index = env_var_get_key_index(options[i], ft_strlen(options[i]));
			if (env_index != FAIL)
			{
				printf("CUURENTT = %s\n", options[i]);
				env_var_del(options[i], env_index);
				env_var_print();
			}
			i++;
		}
	}
}