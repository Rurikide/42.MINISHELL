/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/19 23:03:11 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_list(t_node *head)
{
	t_node	*tmp;

	while (head != NULL)
	{
		tmp = head->next;
		if (head->value != NULL)
			free(head->value);
		if (head->eof != NULL)
			free(head->eof);
		if (head != NULL)
			free(head);
		head = tmp;
	}
}

char	get_type(char *str)
{
	if (ft_is_present('<', str))
	{
		if (str[ft_is_present('<', str) + 1] == '<')
			return ('h');
	}
	else if (ft_is_present('>', str))
	{
		if (str[ft_is_present('>', str) + 1] == '>')
			return ('a');
	}
	else if (str[0] == '\0')
		return ('e');
	return ('c');
}
//minishell> echo "$a" $a  '$a' $a
//		p p '$a' p

//<txt <txt3 <txt7 >txt4 >txt2 >txt7 < txt3 cat <txt > text
//malloc error

//<sdfgdsfg
//ok
//<sdfgdsfg <sdfgdsfgdfg
//malloc error

int	ms_parsing(int i)
{
	t_minishell	*minishell;
	t_node		*list;
	t_node		*tmp;
	char		**arg;

	minishell = get_minishell();
	if (minishell->user_input[0] != '\0' && ms_sanitize(minishell->user_input))
	{
		arg = ms_split(get_var(minishell->user_input, 1, -1), '|', 0, 0);
		minishell->head = new_node(arg[0]);
		if (ft_strlen(arg[0]) == 0)
			return (0);
		while (arg[i] != NULL)
		{
			list = new_node(arg[i++]);
			add_at_end(&minishell->head, list);
		}
		tmp = minishell->head;
		while (tmp->next)
			tmp = tmp->next;
		if (tmp->type == 'e')
			return (0);
		return (1);
	}
	return (0);
}
