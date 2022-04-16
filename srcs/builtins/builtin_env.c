/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:05:56 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/16 17:57:39 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		env_var_is_key_only(char *option)
{
	int i;
	int equal;

	i = 0;
	equal = YES;
	while (option[i])
	{
		if (option[i] == '=')
		{
			equal = NO;
			break ;
		}
		i++;
	}
	return (equal);
}

void	builtin_env(char **options)
{
	env_var_print();
}

	// if (*options != NULL)
	// in case of options should I print?   env: options: No such file or directory