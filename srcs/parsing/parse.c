/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/10 14:57:59 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <string.h>

void	scan_builtins(char **options);

void ms_freeList(struct node* head)
{
	struct node* tmp;

	while (head != NULL)
	{
		tmp = head;
		free(tmp->value);
		head = head->next;
		free(tmp);
	}
}

char	get_type(char *str, char *sym)
{
	char a = sym[0];
	a = 'b';
	if (ft_is_present('<', str))
	{
		if (str[ft_is_present('<', str) + 1] == '<')
			return 'h';
	}
	else if (ft_is_present('>', str))
	{
			if (str[ft_is_present('>', str) + 1] == '>')
				return 'a';
	}
	else if (str[0] == (char)NULL)
			return 'e';
	return 'c';
}

// void	ft_to_do(t_node *head, char *sym)
// {
// 	t_node *tmp1 = head;

// 	if (sym[0] == '!')
// 		printf("Hi");
// 	while (tmp1 != NULL)
// 	{
// 		//tmp1->type = get_type(tmp1->value, sym);
// 		//printf("value:%s, type:%c, fdI:%d, fdO:%d\n", tmp1->value, tmp1->type, tmp1->fdI, tmp1->fdO);
// 		if (tmp1->type == 'c' || tmp1->type == 'a')
// 			scan_builtins(ft_split(tmp1->value, ' '));
// 		else if (tmp1->type == 'p')
// 				printf("and pipe it into\n");
// 		else if (tmp1->type == 'r')
// 			printf("and redirect it into\n");
// 		else if (tmp1->type == 'h')
// 		{
// 			printf("do heredoc bs with %s\n", tmp1->next->value);
// 			tmp1 = tmp1->next;
// 		}
// 		tmp1 = tmp1->next;
// 	}
// }

int ms_parsing(void)
{
	t_minishell *minishell;
	t_node *list;
	t_node *tmp;
	char sym[4] = {'|', '<', '"', '\''}; 
	minishell = get_minishell();
	if (minishell->user_input[0] != '\0' && ms_sanitize(minishell->user_input))
	{
		char **arg = ms_split(get_var(minishell->user_input, 1, -1), '|');
		if (ft_strlen(arg[0]) == 0)
			return 0;
		int i = 1;
		minishell->head = new_node(arg[0], sym);
		while (arg[i] != NULL) {
			list = new_node(arg[i], sym);
			add_at_end(&minishell->head, list);
			i++;
		}
		free(arg);
		tmp = minishell->head;
		//printlist(tmp);
		// ft_to_do(tmp, sym);
	}
	//printf ("%s\n", av[1]);
	return 0;	
}
