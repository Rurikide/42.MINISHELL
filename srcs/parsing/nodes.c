/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/22 12:51:47 by tshimoda         ###   ########.fr       */
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
	tmp = ft_calloc(ft_strlen(str), sizeof(char));
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

	new = malloc(sizeof(t_node));
	if (str != NULL)
	{
		/*if (ft_is_present('\'', str) || ft_is_present('\"', str))
			new->value = ft_strdup(ms_strip(str, 0, 0));
		else
			new->value = ft_strdup(str);*/
		get_var(new, str, 1, -1);
		new->eof = NULL;
		new->type = get_type(str);
		new->fd_i = get_fd_i(new, 0, 0, 0);
		new->fd_o = get_fd_o(new, -1, 0, 1);
		new->id = -1;
		new->flag = NO;
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
