/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:10:52 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/14 16:03:41 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// UNSET deletes an existing env var
// search the environment for the KEY of a KEY=VALUE
// CANNOT UNSET a key ending by an '=' sush as VAR1=    must be VAR1
// POSSIBLE TO UNSET multiple var at the same time. 
// UNSET ALONE DOEST NOTHING SPECIAL

// This function only check if its a valid key name.
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

int	env_var_key_len(char *key);
{
	int len;

	len = 0;
	while (key[len] != '=' && key[len] != '\0')
	{
		len++;
	}
	return(len);
}

int	env_var_matching_key(char *option)
{
	// function verifying if the option key match perfectly one in the env
	t_minishell *minishell;
	int env_index;
	int env_len;
	int opt_len;
	
	// FT_STRLEN
	minishell = get_minishell();
	// loop through all var in env
		
}

void	builtin_unset(char **options)
{
	int i;
	int len;
	int env_index;

	i = 0;
	while (options[i] != NULL)
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
			// env_index = env_var_get_key_index(options[i], ft_strlen(options[i]));
			if (env_index != FAIL)
			{
				printf("ok\n");
				//printf("\033[1;34mdeleted key env var: %s\033[0m \n", options[i]);
				//env_var_del(options[i], env_index);
			}


			i++;
		}
	}
	env_var_print();
}