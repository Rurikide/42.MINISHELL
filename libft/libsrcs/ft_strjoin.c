/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:36:30 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/04 12:27:50 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_symbol(char *str1, char symbol, char *str2)
{
	char	*new_str;
	int		bytes;
	int		i;

	i = 0;
	bytes = ft_strlen(str1) + ft_strlen(str2) + 2;
	new_str = malloc(sizeof(char) * bytes);
	while (str1 != NULL && *str1)
	{
		new_str[i++] = *(str1++);
	}
	new_str[i++] = symbol;
	while (str2 != NULL && *str2)
	{
		new_str[i++] = *(str2++);
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	unsigned int	bytes;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	bytes = (ft_strlen(s1) + ft_strlen(s2) + 1);
	newstr = ft_calloc(bytes, sizeof(char));
	if (!newstr)
		return (0);
	while (s1 != NULL && s1[j])
		newstr[i++] = s1[j++];
	j = 0;
	while (s2 != NULL && s2[j])
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	s1 = NULL;
	return (newstr);
}

	//newstr = malloc(sizeof(char) * bytes);