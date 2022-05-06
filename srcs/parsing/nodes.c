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

char *ms_strip(char *str, int i, int j)
{
	char *tmp = ft_calloc(ft_strlen(str), sizeof(char));
	char s = check_qm(str, -1, 1, 1);
	char d = check_qm(str, -1, 1, 1);

	if (str[i] == ' ')
		i++;
	printf("i = %d, 1st char = %d\n", i, (int)str[i]);
	while (str[i])
	{
		if (s == 0 && str[i] == '\'')
			i++;
		else if (d == 0 && str[i] == '"')
			i++;
		tmp[j++] = str[i++];
	}
	free(str);
	return (tmp);
}

t_node	*new_node(char *str, char *sym)
{
	t_node	*new = malloc(sizeof(t_node));
	new->value = ms_strip(str, 0, 0);
	new->type = get_type(str, sym);
	new->fdI = get_fdI(new, 0, 0);
	new->fdO = get_fdO(new, 0, 0, 1);
	new->next = NULL;
	return new;
}

void	printlist(t_node *head)
{
	t_node *tmp = head;

	while (tmp != NULL)
	{
		printf("Value:%s\n", tmp->value);
		printf("Type:%c\n", tmp->type);
		tmp = tmp->next;
	}
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
	tmp->next = new;
	return 0;
}
