/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:15:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/15 17:04:28 by tshimoda         ###   ########.fr       */
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

// a verifier avec Alex sil enleve le backslash
void	ft_swap(char **s1, char **s2)
{
	char *temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	env_var_print_in_order(t_minishell *ms, int i, int j)
{
	char **table;

	table = ft_calloc(ms->env_size, sizeof(char *));
	while (ms->env[i] != NULL)
	{
		table[i] = ft_strdup(ms->env[i]);
		i++;
	}
	i = 0;
	while (table[i] != NULL)
	{
		j = i + 1;
		while (table[j] != NULL)
		{

			if (ft_strcmp(table[i], table[j]) > 0)
				ft_swap(&table[i], &table[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (table[i])
		printf("%s\n", table[i++]);
	ft_free_table(table);
}

// 45 - 46 . 47 / 58 : 95 _ 34 "
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

int	evaluate_export_key(char *option)
{
	int i;
	int equal;

	i = 1;
	equal = NO;
	if (!ft_isalpha(option[0]) && option[0] != '_')
	{
		printf("ici\n");
		return (FAIL);
	}
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
		// CHECK UP POUR UNE VALID KEY
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

	i = 0;
	// If there are no options, EXPORT print env is alpha order
	if (options[i] == NULL)
	{
		env_var_print_in_order(get_minishell(), 0, 0);
		return ;
	}
	while (options[i])
	{
		printf("option: %s\n", options[i]);
		int type = evaluate_export_key(options[i]);
		printf("type: %d\n", type);

		// ENSUITE VERIFIER SI LA KEY EXISTE DANS ENV
		/*
		si la key=value existe deja avec une valeur
		type1 = no update
		typ2 & 3 = update

		si cest a key=
		type1 = no update
		typ2 & 3 = update

		si la key SEUL pas de =
		type1 = no update
		typ2 & 3 = update

	si la key nexiste pas
	NEW ENV VAR!
		*/
		// si le type == 1

		i++;
	}
}