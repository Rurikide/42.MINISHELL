/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:15:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/12 15:37:07 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// function adding an env var if there is options 
// BASH export KEY without =VALUE adds a new env var with just the name
// export KEY= without value outputs KEY=""
// IF THE env var already exist, it will update it!!!
// EXPORT CAN ADD MULTIPLE VAR AT ONCE
// IF THE VAR EXIST and you try export just the KEY, the VAR will remain unchanged
// IF THE VAR EXIST and you try to export with KEY= it will be updated.
// IF ITS THE SAME ENV VAR, it will update with the lastest entry


// VALID KEY ABCabc underscore_ 
// slash / = invalid identifier???


// EXEMPLE DE INPUT
// options[0] == VAR1       -> VAR1
// options[1] == VAR2=      -> VAR2=""
// options[2] == VAR3=abc   -> VAR3=abc
// a verifier avec Alex sil enleve le backslash

// int	export_type_key_value(char *option)
// {
// 	int	type;
// 	int i;
// 	// type 0 == error invalid identifier
// 	// type 1 == valid key
// 	// type 2 == key followed by '='
// 	// type 3 == key=value pair 
// 	type = 0;
// 	i = 0;
// 	if (!ft_isalpha(option[i]) && option[i] != '_')
// 		return (type);
// 	else
// 		type = 1;
// 	i++;
// 	while (option[i] != '\0' && type == 1)
// 	{
// 		if (option[i] == '=')
// 			type = 2;
// 		i++;
// 	}
// 	if (option[i] != '\0')
// 		type = 3; 
// 	return (type);
// }

// function returning the name of the key
// char *export_get_key(char *option)
// {
	
// }

// void	builtin_export(char **options)
// {
// 	t_minishell *minishell;
// 	int i;
// 	int j;
// 	int len;
// 	int type;

// 	i = 0;
// 	j = 0;
// 	len = 0;
// 	minishell = get_minishell();
// 	if (options[i] == NULL)
// 		return ;

// 	while (options[i] != NULL)
// 	{
// 		printf("options[%d] == %s\n", i, options[i]);
// 		type = export_type_key_value(options[i]);
// 		printf("type = %d\n", type);
// 		if (type == 0)
// 			printf("error identifier\n");
// 		else if (type == 1)
// 		{
// 			env_var_update()
// 		}
// 		else if (type == 2)
// 		{
// 			printf("type 2\n");
// 		}
// 		else if (type == 3)
// 		{
// 			printf("type 3\n");
// 		}
// 		i++;
// 	}
// }

// check sil y a un doublon de KEY
// check sil y a un KEY= dans loption


// unset SHLVL donne SHLVL=1
// unset PWD   delete, mais garde en memoire. 