/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:19:38 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/10 14:59:29 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ms_check_pipes(char *input, int i)
{
	int j;
	int r;

	j = i;
	r = 0;
	while (input[j--])
	{
		if (ft_isalnum(input[j]))
		{
			r += 1;
			break;
		}
	}
	while (input[i++])
	{
		if (ft_isalnum(input[i]))
		{
			r += 1;
			break;
		}
	}
	if (r < 2)
		printf("syntax error near unexpected token `|'\n");
	printf("r = %d\n", r);
	return (r);
}

int ms_sanitize(char *input)
{
	int	i;
	int r;

	i = 0;
	r = 0;

	while(input[i])
	{
		if (input[i] == '|')
		{
			r = ms_check_pipes(input, i);
			if (r < 2)
				return (0);
		}
		i++;
	}
	return (1);
}
