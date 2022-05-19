/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:24 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/18 17:16:07 by adubeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_is_present(char c, char *sym);

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!dest || !src)
		return (0);
	if (n > 0)
	{	
		while (--n && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

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

static unsigned int	ft_get_nb_strs(char const *s, char sym)
{
	int				i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 1;
	while (s[i])
	{
		if (s[i] == '"')
		{
			while (s[i++])
			{
				if (s[i] == '"')
					break ;
				else if (i == ft_strlen(s))
				{
					printf("Error missing \"\n");
					return (0);
				}
			}
		}
		if (s[i] == '\'')
		{
			while (s[i++])
			{
				if (s[i] == '\'')
					break ;
				else if (i == ft_strlen(s))
				{
					printf("Error missing \'\n");
					return (0);
				}
			}
		}
		if (s[i] == sym)
			nb_strs++;
		i++;
	}
	return (nb_strs);
}

static void	ft_get_next_str(char **next_str, unsigned int *next_str_len,
					char sym)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while ((*next_str)[i] == sym)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == sym)
			return ;
		if ((*next_str)[i] == '"')
		{
			while ((*next_str)[i])
			{
				(*next_str_len)++;
				i++;
				if ((*next_str)[i] == '"')
					break ;
			}
		}
		if ((*next_str)[i] == '\'')
		{
			while ((*next_str)[i])
			{
				(*next_str_len)++;
				i++;
				if ((*next_str)[i] == '\'')
					break ;
			}
		}
		(*next_str_len)++;
		i++;
	}
}

char	**ms_split(char const *s, char sym)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	i = 0;
	if (ft_strlen(s) == 0)
		return ((char **)s);
	nb_strs = ft_get_nb_strs(s, sym);
	tab = (char **)malloc(sizeof(char *) * (nb_strs + 1));
	if (!tab || !s)
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, sym);
		tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
