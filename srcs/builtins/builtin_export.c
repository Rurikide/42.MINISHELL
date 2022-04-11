/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:15:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/11 13:00:12 by tshimoda         ###   ########.fr       */
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



// // FINALLY PRINTS all the env var
// t_answer export_option(char *option)
// {
// 	size_t i;

// 	i = 0;
		
// }

// void	builtin_export(char **options)
// {
// 	t_minishell *minishell;
// 	size_t i;
// 	size_t j;
// 	size_t len;

// 	i = 0;
// 	j = 0;
// 	len = 0;
// 	minishell = get_minishell();
// 	// looping to check every env var input
// 	while (options[i] != NULL)
// 	{
// 		len = ft_strlen(options[i]);
// 		j = 0;
// 		while (minishell->env[j] != NULL)
// 		{
// 			minishell->env[j]
// 			j++;
// 		}
// 		i++;
// 	}
// }

// check sil y a un doublon de KEY
// check sil y a un KEY= dans loption