/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:13:07 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/01 15:42:39 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *ft_trim(char *str, char c)
// {
// 	char	*tmp;
// 	int 	i;
// 	int 	j;

// 	i = 0;
// 	j = 0;
// 	//freeeeeeeeee meeeeeeeeee
// 	tmp = ft_calloc(ft_strlen(str), sizeof(char));
// 	while (str[i])
// 	{
// 		if (str[i] != c)
// 			tmp[j++] = str[i];
// 		i++;
// 	}
// 	return (tmp);
// }

// t_answer	ft_is_a_match(char *keyword, char *input)
// {
// 	int		i;
// 	int		len;
// 	char	*tmp;

// 	i = 0;
// 	if (input == NULL)
// 		return (NO);
// 	tmp = ft_trim(input, ' ');
// 	len = ft_strlen(tmp);
// 	if (ft_strlen(keyword) != ft_strlen(tmp))
// 	{
// 		free(tmp);
// 		return (NO);
// 	}
// 	while (i < len)
// 	{
// 		if (keyword[i] == tmp[i])
// 			i++;
// 		else
// 		{
// 			free(tmp);
// 			return (NO);
// 		}
// 	}
// 	free(tmp);
// 	return (YES);
// }

t_answer	ft_is_a_match(char *keyword, char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	if (input == NULL)
		return (NO);
	if (ft_strlen(keyword) != ft_strlen(input))
		return (NO);
	while (i < len)
	{
		if (keyword[i] == input[i])
			i++;
		else
			return (NO);
	}
	return (YES);
}

t_answer	ft_is_option(char valid, char *list)
{
	size_t	i;

	i = 0;
	if (list[i] == '\0')
		return (NO);
	while (list[i] != '\0')
	{
		if (valid == list[i])
			i++;
		else
			return (NO);
	}
	return (YES);
}

char	**ft_table_add(char **table, const char *new)
{
	char	**deepcopy;
	int		i;

	i = -1;
	deepcopy = ft_calloc(ft_table_len(table) + 2, sizeof(char *));
	if (deepcopy == NULL)
		return (NULL);
	while (table[++i] != NULL)
		deepcopy[i] = ft_strdup(table[i]);
	deepcopy[i] = ft_strdup(new);
	deepcopy[i + 1] = NULL;
	ft_free_table(table);
	return (deepcopy);
}

void	ft_table_del(char **table, int index)
{
	if (index >= ft_table_len(table))
		return ;
	free(table[index]);
	while (table[index] != NULL)
	{
		table[index] = table[index + 1];
		index++;
	}
}
