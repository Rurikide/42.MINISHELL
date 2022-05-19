/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:19:38 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/18 17:18:33 by adubeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_is_present(char c, char *sym)
{
	int	i;

	i = 0;
	while (sym[i])
	{
		if (sym[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ms_check_pipes(char *input, int i)
{
	int	j;
	int	r;

	j = i;
	r = 0;
	while (input[j--])
	{
		if (ft_isalnum(input[j]))
		{
			r += 1;
			break ;
		}
	}
	while (input[i++])
	{
		if (ft_isalnum(input[i]))
		{
			r += 1;
			break ;
		}
	}
	if (r < 2)
		printf("minishell: syntax error near unexpected token `|'\n");
	return (r);
}

int	ms_sanitize(char *input)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (input[i])
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
