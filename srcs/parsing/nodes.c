/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/18 17:02:31 by adubeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <string.h>

char	*ms_strip(char *str, int i, int j)
{
	char	*tmp;

	tmp = ft_calloc(ft_strlen(str), sizeof(char));
	if (!str)
		return (NULL);
	if (!(ft_isprint(str[i])))
		i++;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				tmp[j++] = str[i];
		}
		else if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
				tmp[j++] = str[i];
		}
		else
			tmp[j++] = str[i++];
	}
	free(str);
	return (tmp);
}

t_node	*new_node(char *str)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (str != NULL)
	{
		if (ft_is_present('\'', str) || ft_is_present('\"', str))
			new->value = ms_strip(str, 0, 0);
		else
			new->value = str;
		new->eof = NULL;
		new->type = get_type(str);
		new->fd_i = get_fd_i(new, new->value, 0, 0, 0);
		new->fd_o = get_fd_o(new, new->value, 0, 0, 1);
		new->id = -1;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

t_node	*add_at_head(t_node **head, t_node *new)
{
	new->next = *head;
	*head = new;
	return (new);
}

void	*add_at_end(t_node **head, t_node *new)
{
	t_node	*tmp;

	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
	return (0);
}
