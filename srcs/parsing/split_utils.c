/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:37:11 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/03 14:52:47 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_symbol(char const *s, char sym, int *i)
{
	while (s[*i] == sym)
	{
		*i += 1;
	}
}

void	skip_symbol_increment_strs(char const *s, char sym, \
		int *i, unsigned int *nb_strs)
{
	while (s[*i] == sym)
	{
		*i += 1;
	}
	if (s[*i])
		*nb_strs += 1;
}

void	increment_index(char const *s, int *i)
{
	if (s[*i])
		*i += 1;
}
