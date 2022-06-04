/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:24 by adubeau           #+#    #+#             */
/*   Updated: 2022/06/04 10:44:55 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static unsigned int	ft_get_nb_strs(char const *s, char sym, int i, \
								unsigned int nb_strs)
{
	char	q;

	if (!s[0])
		return (0);
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			q = s[i];
			i++;
			while (s[i])
			{
				if (s[i] == q)
					break ;
				else if (i == ft_strlen(s) - 1)
					printf("minishell: Error missing %c\n", q);
				else if (i == ft_strlen(s) - 1)
					return (0);
				i++;
			}
		}
		if (s[i] == sym)
			nb_strs++;
	}
	return (nb_strs);
}

/*static void	ft_get_next_quote(char **next_str, unsigned int *next_str_len, \
								char c, unsigned int *i)
{
	while ((*next_str)[*i])
	{
		(*next_str_len)++;
		(*i)++;
		if ((*next_str)[*i] == c)
			return ;
	}
}*/

static void	ft_get_next_str(char **next_str, unsigned int *next_str_len, \
							char sym, unsigned int i)
{
	char	q;

	q = '\0';
	*next_str += *next_str_len;
	*next_str_len = 0;
	while ((*next_str)[i] && (*next_str)[i] == sym)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == '"' || (*next_str)[i] == '\'')
		{
			q = (*next_str)[i];
			(*next_str_len)++;
			i++;
			while ((*next_str)[i] && (*next_str)[i] != q)
			{
				(*next_str_len)++;
				i++;
			}
		}
		if ((*next_str)[i++] == sym)
			return ;
		// if ((*next_str)[i])
			(*next_str_len)++;
	}
}

char	**ms_split(char const *s, char sym, unsigned int i, \
		unsigned int next_str_len)
{
	char			**tab;
	char			*next_str;
	unsigned int	nb_strs;

	if (ft_strlen(s) == 0)
		return ((char **)s);
	nb_strs = ft_get_nb_strs(s, sym, -1, 1);
	tab = (char **)malloc(sizeof(char *) * (nb_strs + 1));
	if (!tab || !s)
		return (NULL);
	next_str = (char *)s;
	while (i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, sym, 0);
		tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

	//
	//printf("nb strs:%d\n", nb_strs);