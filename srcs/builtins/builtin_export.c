/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:15:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/21 17:22:25 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// a verifier avec Alex sil enleve le backslash

// #45 '-' #46 '.' #47 '/' #58 ':' #61 '=' #95 '_'


// int	env_var_valid_value(char *line, int i, int j)
// {
// 	char	*charset;
// 	int		valid;

// 	charset = (char [7]){45, 46, 47, 58, 61, 95};

// 	i = 0;
// 	while (line[i])
// 	{
// 		valid = FAIL;
// 		if (ft_isalnum(line[i]))
// 			valid = SUCCESS;
// 		else if (!ft_isalnum(line[i]))
// 		{
// 			j = 0;
// 			while (charset[j])
// 			{
// 				if (line[i] == charset[j])
// 					valid = SUCCESS;
// 				j++;
// 			}
// 		}
// 		if (valid == FAIL)
// 		{
// 			printf("Found invalid character");
// 			return (FAIL);
// 		}
// 		i++;
// 	}
// 	return (SUCCESS);
// }

int	evaluate_export_type(char *option)
{
	int i;
	int equal;

	i = 1;
	equal = NO;

	// TYPEFAIL INVALID KEY, TYPE1: KEY ONLY,    TYPE2: KEY=,  TYPE3: KEY=VALUE

	if (!ft_isalpha(option[0]) && option[0] != '_')
		return (FAIL);
	while (option[i])
	{
		// IF THERE IS AN EQUAL SYMBOL
		if (option[i] == '=')
		{
			equal = YES;
			if (option[i + 1] == '\0')
				return (2);
			else 
			{
				// if 	(env_var_valid_value(&option[i], 0, 0) == FAIL)
				// 	return (FAIL);
				return (3);
			}
		}
		if (!ft_isalnum(option[i]) && option[i] != '_' && equal == NO)
			return (FAIL);
		if (option[i] == '/' && equal == NO)
			return(FAIL);
		i++;
	}
	return(1);
}

void	builtin_export(char **options)
{
	int i;
	int type;
	int pos;

	i = 0;
	get_minishell()->exit_nb = SUCCESS;
	if (options[i] == NULL)
	{
		env_var_print_in_order(get_minishell(), 0, 0);
		return ;
	}
	while (options[i])
	{
		// TYPE1: KEY ONLY    TYPE2: KEY=  TYPE3: KEY=VALUE
		// if ()
		// {
		// 	printf("export: %s: not a valid identifier\n", options[i]);
		// 	get_minishell()->exit_nb = ERROR_1;
	// }
		type = evaluate_export_type(options[i]);
		pos = env_var_matching_key(options[i]);
		printf("type = %d and pos = %d\n", type, pos);
		
		// if la var existe deja et de type 2 ou 3
		if ((type == 2 || type == 3) && pos != FAIL)
		{
			printf("premier if\n");
			env_var_export_update(options[i], pos, NO);
		}
		
		
		// else if new var de type 2 ou 3
		else if ((type == 2 || type == 3) && pos == FAIL)
		{
			printf("else if 1\n");
			env_var_export_update(options[i], pos, YES);
		}
		
		
		// else if its a new variable!!!
		else if (type == 1 && pos == FAIL)
		{
			printf("else if 2\n");
			env_var_export_update(options[i], pos, YES);
		}

		i++;
	}
}

// POOURRQUOI   ./minishell "export type=shadoow TERM= ZSH=ciaobye LESS _=/R" ??? le dernier print avant le type=shadoow