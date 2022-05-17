/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/17 15:48:20 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <string.h>

char *ms_strip(char *str, int i, int j)
{
	char *tmp = ft_calloc(ft_strlen(str), sizeof(char));
//	printf("ms_strip str='%s'\n", str);
	if (!str)
		return NULL;
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
	//free(str);
	//printf("ms_tmp =%s\n", tmp);
	//garbage when echo "a" | dfsgdsfg
	return (tmp);
}

t_node	*new_node(char *str, char *sym)
{
//	printf("new->str:'%s'\n", str);

	t_node	*new = malloc(sizeof(t_node));
	//new->fdO = get_fdO(str, 0, 0, 1);
	if (str != NULL) {
		if (ft_is_present('\'', str) || ft_is_present('\"', str))
			new->value = ms_strip(str, 0, 0);
		else
			new->value = str;
	//	printf("new->value:'%s'\n", new->value);
		new->eof = NULL;
		new->type = get_type(str, sym);
		new->fd_i = get_fdI(new, 0, 0);
		new->fd_o = get_fdO(new, new->value, 0, 0, 1);
		new->id = -1;
		new->next = NULL;
		new->prev = NULL;
		//	printf("new->value:'%s'\n", new->value);
	}


	return new;
}

void	printlist(t_node *head)
{
	t_node *tmp = head;

	while (tmp->next != NULL)
	{
	//	printf("Value:%s\n", tmp->value);
	//	printf("Type:%c\n", tmp->type);
		tmp = tmp->next;
	}
	/*while (tmp != NULL)
	{
		printf("Value:%s\n", tmp->value);
		printf("Type:%c\n", tmp->type);
		tmp = tmp->prev;
	}*/
}

t_node	*add_at_head(t_node **head, t_node *new)
{
	new->next = *head;
	*head = new;
	return new;
}

void	*add_at_end(t_node **head, t_node *new)
{
	t_node *tmp = *head;

	while (tmp->next != NULL)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
	return 0;
}