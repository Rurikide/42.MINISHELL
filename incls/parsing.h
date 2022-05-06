/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubeau <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:50:49 by adubeau           #+#    #+#             */
/*   Updated: 2022/04/30 16:31:38 by adubeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

#ifndef PARSING_H
# define PARSING_H

struct node
{
	char	*value;
	char	type;
	int		fdI;
	int		fdO;
	struct  node *next;

};

typedef struct node t_node;

char check_qm (char *str, int i, int s, int d);
int		get_fdI(t_node *current, int i, int j);
int		get_fdO(t_node *current, int i, int j, int fd);
char 	*get_var(char *str, int quote, int i);
t_node	*add_at_head(t_node **head, t_node *new);
void	*add_at_end(t_node **head, t_node *new);
char	get_type(char *str, char *sym);
t_node	*new_node(char *str, char *sym);
void	printlist(t_node *head);
void	ft_to_do(t_node *head, char *sym);
int ms_parsing();
int	ft_is_present(char c, char *sym);
char	**ms_split(char const *s, char sym);

#endif
