/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:43:55 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/26 17:05:02 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
		free(table[i++]);
	free(table);
	//
	printf("ici dans ft_free_Table!!!\n");
}
