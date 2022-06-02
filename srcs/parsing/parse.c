/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/06/02 18:54:11 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_list(t_node *head)
{
	t_node	*tmp;

	tmp = NULL;
	while (head != NULL)
	{
		tmp = head->next;
		if (head->value != NULL)
		{
			free(head->value);
			head->value = NULL;
		}
		if (head->eof != NULL)
		{
			free(head->eof);
			head->eof = NULL;
		}
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

void	ms_arg_to_node(t_minishell *minishell, char **arg, int i)
{
	t_node		*list;

	while (arg[i] != NULL)
	{
		list = new_node(arg[i++]);
		add_at_end(&minishell->head, list);
	}
	ft_free_table(arg);
}

int	ms_parsing(t_minishell *minishell, int i)
{
	t_node		*tmp;
	char		**arg;

	if (minishell->user_input[0] != '\0' && ms_sanitize(minishell->user_input))
	{
		arg = ms_split(minishell->user_input, '|', 0, 0);
		minishell->head = new_node(arg[0]);
		if (ft_strlen(arg[0]) == 0)
		{
			ft_free_table(arg);
			return (0);
		}
		ms_arg_to_node(minishell, arg, i);
		tmp = minishell->head;
		while (tmp->next)
		{
			if (tmp->flag == YES)
				return (0);
			tmp = tmp->next;
		}
		if (tmp->flag == YES || tmp->type == 'e')
			return (0);
		return (1);
	}
	return (0);
}

		// while (arg[i] != NULL)
		// {
		// 	list = new_node(arg[i++]);
		// 	add_at_end(&minishell->head, list);
		// }