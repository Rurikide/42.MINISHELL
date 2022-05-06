/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubeau <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:24 by adubeau           #+#    #+#             */
/*   Updated: 2022/04/30 17:51:18 by adubeau          ###   ########.fr       */
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
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i])
	{
		if (s[i] == '"')
			while (s[i])
			{
				i++;
				if (s[i] == '"')
					break;
			}
		if (s[i] == '\'')
        	while (s[i])
            {
            	i++;
                if (s[i] == '\'')
                	break;
            }
		if (s[i] == sym)
			nb_strs++;
		i++;
	}
	return (nb_strs + 1);
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
					break;
			}
		}
		if ((*next_str)[i] == '\'')
		{
			while ((*next_str)[i])
			{
				(*next_str_len)++;
				i++;
				if ((*next_str)[i] == '\'')
					break;
			}
		}
		(*next_str_len)++;
		i++;
	}
}

int	ft_is_present(char c, char *sym)
{
	int i;

	i = 0;
	while (sym[i])
	{
		if (sym[i] == c)
			return i;
		i++;
	}
	return 0;
}

char check_qm (char *str, int i, int s, int d)
{
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			s *= -1;
			i++;
			while (str[i] && str[i + 1] != '\'')
				i++;
		}
		else if (str[i] == '"')
		{
			d *= -1;
			i++;
			while (str[i + 1] && str[i + 1] != '"')
				i++;
		}
	}
	if (s < 0)
		return ('\'');
	else if (d < 0)
		return ('"');
	else
		return (0);
}

char	**ms_split(char const *s, char sym)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	nb_strs = ft_get_nb_strs(s, sym);
	printf("nb_str = %d\n", nb_strs);
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
		if (check_qm(next_str, -1, 1, 1) != 0)
			ft_strlcpy(tab[i], "", 1);
		else
			ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
