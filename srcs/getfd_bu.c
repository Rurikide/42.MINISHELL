/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubeau <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/04/30 16:34:26 by adubeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <string.h>

int		get_fdI(t_node *current, int i, int j)
{

	int fd;
	char *file;

	fd = 0;
	while (current->value[i])
	{
		if (current->value[i] == ('<'))
			if (current->value[i + 1] != '<')
			{
				while (!(ft_isalnum(current->value[i])))
					i++;
				while (ft_isalnum(current->value[i++]))
					j++;
				file = ft_substr(current->value, i-j, j);
				fd = open(file, O_RDONLY);
			}
		i++;
	}
	return (fd);
}
int	get_fdO(t_node *current, int i, int j, int fd)
{
	int k;
	char *file;
	char *tmp;

	while (current->value[i])
	{
		if (current->value[i] == '>')
		{
			k = i - 1;
			while (current->value[i] == ' ' || current->value[i] == '>')
				i++;
			while (current->value[i] && current->value[i] != ' ' && current->value[i] != '>')
			{
				j++;
				i++;
			}
			file = ft_substr(current->value, i - j, j);
			if (ft_is_present('/', file))
			{
				current->value = "";
				printf("%s: No such file or directory\n", file);
				return (1);
			}
			printf("\nfile:%s\n", file);
			tmp = ft_strjoin(ft_substr(current->value, 0, k + 1), (current->value + i));
			free(current->value);
			current->value = tmp;
			free(tmp);
			if (current->type == 'c')
				fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
			else
				fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
			return (get_fdO(current, 0, 0, fd));
		}
		i++;
	}
	return (fd);
}
