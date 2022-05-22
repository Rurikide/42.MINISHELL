/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/22 11:52:53 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_expand(char *str, int i)
{
	int		j;
	char	*tmp;
	char	*var;
	char	*res;

	j = 0;
	while (str[i + j] && str[i + j] != ' ' && str[i + j] != '$' \
			&& str[i + j] != '\'' && str[i + j] != '"')
		j++;
	tmp = ft_substr(str, 0, i - 1);
	if (str[i] == '?')
		var = ft_itoa(get_minishell()->exit_nb);
	else
		var = env_var_get_value(ft_substr(str, i, j), j);
	if (var == NULL)
		res = ft_strjoin(tmp, &str[i + j]);
	else
	{
		res = ft_strjoin(tmp, var);
		//free(var);
		free(tmp);
		res = ft_strjoin(res, &str[i + j]);
	}
	return (res);
}

char	*get_var(char *str, int quote, int i)
{
	int	j;

	j = 0;
	if (ft_strlen(str) == 0)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			quote *= -1;
			i++;
		}
		else if (str[i] == '$' && str[i++] && quote > 0)
			return (get_var(ms_expand(str, i), quote, i - 1));
	}
	return (str);
}
