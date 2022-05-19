/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getfd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/19 11:48:08 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <string.h>

int	get_fd_i(t_node *current, char *value, int i, int j, int fd)
{
	int		k;
	char	*file;
	char	*tmp;

	while (value[i])
	{
		j = 0;
		if (value[i] == '<')
		{
			k = i;
			while (value[i] == ' ' || value[i] == '<')
				i++;
			while (value[i] && value[i] != ' ' && value[i] != '<')
			{
				j++;
				i++;
			}
			file = ft_substr(value, i - j, j);
			fd = open(file, O_RDONLY);
			if (fd == -1)
			{
				current->type = 'e';
				printf("%s: No such file or directory\n", file);
				break ;
			}
			tmp = ft_strjoin(ft_substr(value, 0, k), (value + i));
			free(value);
			value = tmp;
			tmp = NULL;
			i = -1;
		}
		i++;
	}
	current->value = value;
	return (fd);
}

int	get_fd_o(t_node *current, char *value, int i, int j, int fd)
{
	int		k;
	char	*file;
	char	*tmp;
	char	type;

	while (value[i])
	{
		j = 0;
		if (value[i] == '>')
		{
			k = i - 1;
			if (value[i + 1] == '>')
			{
				current->type = 'a';
				i++;
			}
			else
				type = 'c';
			while (value[i] == ' ' || value[i] == '>')
				i++;
			while (value[i] && value[i] != ' ' && value[i] != '>')
			{
				j++;
				i++;
			}
			file = ft_substr(value, i - j, j);
			if (ft_is_present('/', file))
				printf("minishell: %s: No such file or directory\n", file);
			tmp = ft_strjoin(ft_substr(value, 0, k), (value + i));
			free(value);
			value = tmp;
			tmp = NULL;
			printf("file = %s, value = %s, type = %c\n", file, value, current->type);
			if (type == 'c')
			{
				fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
				//free(file);
			}
			else
			{
				fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
				//free(file);
			}
			i = -1;
		}
		i++;
	}
	current->value = value;
	return (fd);
}
