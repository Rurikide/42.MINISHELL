/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/10 14:59:04 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <string.h>

static char *ms_expand(char *str, int i)
{
	int j;
	char *tmp;
	char *var;
	char *res;

	j = 0;
	while(str[i + j] && str[i + j] != ' ' && str[i + j] != '$' && str[i + j] != '\'' && str[i+j] != '"')
		j++;
	var = env_var_get_value(ft_substr(str, i, j), j);
	printf("i = %d, j = %d\n", i, j);
	tmp = ft_substr(str, 0, i - 1);
	if (var == NULL)
		res = ft_strjoin(tmp, &str[i + j]);
	else
		res = ft_strjoin(ft_strjoin(tmp, var), &str[i + j]);
	//printf("res = '%s', strlen = %i\n", res, ft_strlen(res));
	free(tmp);
	return (res);
}

char *get_var(char *str, int quote, int i)
{
	while (str[++i] && str[i + 1])
	{
		if (str[i] == '\'')
		{
			quote *= -1;
			i++;
		}
		if (str[i] == '$' && str[i + 1] && quote > 0)
			return (get_var(ms_expand(str, ++i), quote, -1));
	}
	return (str);
}
	/*int	i;
	int	j;
	char *var = NULL;
	char *tmp = NULL;
	char *str = NULL;

	i = 0;
	j = 0;
	if (!(ft_is_present('$', str1)))
		return (str1);
	while (str1[i + j])
	{
		while (str1[i] != '$')
		{
			i++;
		}
		tmp = ft_memcpy(tmp, str1, i);
		i++;
		while (ft_isalnum(str1[i++]))
			j++;
		var = env_var_get_value(ft_substr(str1, i-j-1, j), j);
		str = ft_strjoin(str, ft_strjoin(tmp, var));
	}
	return (ft_strjoin(tmp,ft_strjoin(var, ft_substr(str1, i+j, ft_strlen(str1 - (i + j))))));
}*/
