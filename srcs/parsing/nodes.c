/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/06/04 12:00:13 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_strip(char *str, int i, int j)
{
	char	*tmp;
	int		s;
	int		d;

	s = 1;
	d = 1;
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '\'' && d > 0)
		{
			i++;
			s *= -1;
		}
		else if (str[i] == '\"' && s > 0)
		{
			i++;
			d *= -1;
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

	new = ft_calloc(1, sizeof(t_node));
	if (str != NULL)
	{
		new->value = ft_calloc(ft_strlen(str) + get_length(str, -1, 0, 0) + 1, \
		sizeof(char));
		get_var(new, str, 1, -1);
		new->eof = NULL;
		new->type = get_type(str);
		new->fd_i = get_fd_i(new, 0, 0, 0);
		new->fd_o = get_fd_o(new, -1, 0, 1);
		new->flag = NO;
		new->id = -1;
		new->prev = NULL;
		new->next = NULL;
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
