/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:58:38 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/03 18:17:46 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_matching_strings(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1) - 1;
	s2_len = ft_strlen(s2) - 1;
	if (s1_len != s2_len)
		return (FAIL);
	while (s1_len > 0 && s2_len > 0)
	{
		if (s1[s1_len] != s2[s2_len])
			return (FAIL);
		s1_len--;
		s2_len--;
	}
	return (SUCCESS);
}

void	ft_close_pipe(int *pipe_end)
{
	close(pipe_end[0]);
	close(pipe_end[1]);
}

int	ft_is_str_spacetab(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	ft_count(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

void	ft_iterate(t_node *cu, int *i, char q)
{
	*i += 1;
	while (cu->value[*i] && cu->value[*i] != q)
		*i += 1;
}
