/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:15:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/20 12:13:35 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// a verifier avec Alex sil enleve le backslash

// #45 '-' #46 '.' #47 '/' %58 ':' #95 '_' #34 '"'


// int	special_value_ascii(char *line, int i, int j)
// {
// 	char	*charset;
// 	int		valid;

// 	charset = (char [6]){45, 46, 47, 58, 95};

// 	i = 0;
// 	while (line[i])
// 	{
// 		valid = 0;
// 		j = 0;
// 		while (charset[j])
// 		{
// 			if (line[i] == charset[j])
// 				valid = 1;
// 			j++;
// 		}
// 		if (valid == 0)
// 			printf("Found invalid character");
// 		i++;
// 	}
// 	return (valid);
// }

int	evaluate_export_type(char *option)
{
	int i;
	int equal;

	i = 1;
	equal = NO;
	if (!ft_isalpha(option[0]) && option[0] != '_')
		return (FAIL);
	while (option[i])
	{
		if (option[i] == '=')
		{
			equal = YES;
			if (option[i + 1] == '\0')
				return (2);
			else 
				return (3);
		}
		if (!ft_isalnum(option[i]) && option[i] != '_' && equal == NO)
		{
			printf("incorrect key\n ");
			return (FAIL);
		}
		//
		// fonction qui regarde les caractere dans les values
		//
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
	int	printer;
	
	i = 0;
	get_minishell()->exit_nb = SUCCESS;
	if (options[i] == NULL)
	{
		env_var_print_in_order(get_minishell(), 0, 0);
		return ;
	}
	while (options[i])
	{
		if (is_only_key_identifier(options[i]) == NO)
		{
			printf("unset: %s: not a valid identifier\n", options[i]);
			printer = NO;
			get_minishell()->exit_nb = ERROR_1;
		}
		type = evaluate_export_type(options[i]);
		// TYPE1: KEY ONLY    TYPE2: KEY=  TYPE3: KEY=VALUE
		pos = env_var_matching_key(options[i]);
		// if la var existe deja et de type 2 ou 3
		if ((type == 2 || type == 3) && pos != FAIL)
			env_var_export_update(options[i], pos, NO);
		// else if new var de type 2 ou 3
		else if ((type == 2 || type == 3) && pos == FAIL)
			env_var_export_update(options[i], pos, YES);
		// else if its a new variable!!!
		else if (type == 1 && pos == FAIL)
			env_var_export_update(options[i], pos, YES);
		i++;
	}
	if (printer != NO)
		env_var_print_in_order(get_minishell(), 0, 0);
}

// POOURRQUOI   ./minishell "export type=shadoow TERM= ZSH=ciaobye LESS _=/R" ??? le dernier print avant le type=shadoow