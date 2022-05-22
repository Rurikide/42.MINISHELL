/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/22 14:00:21 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_expand(char *str, int i)
{
	int		j;
	char	*tmp;
	char	*tmp1;
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
	{
		tmp1 = ft_substr(str, i, j);
		var = env_var_get_value(tmp1, j);
		free(tmp1);
	}
	if (var == NULL)
		tmp = ft_strjoin(tmp, &str[i + j]);
	else
	{
		res = ft_strjoin(tmp, var);
		if (str[i] == '?')
			free(var);
		free(tmp);
		tmp = NULL;
		tmp = ft_strjoin(res, &str[i + j]);
		free(res);
	}
	return (tmp);
}

void	get_var(t_node *current, char *str, int quote, int i)
{
	int		j;
	char *tmp;

	j = 0;
	tmp = NULL;
	if (ft_strlen(str) == 0)
		return ;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			quote *= -1;
			i++;
		}
		else if (str[i] == '$' && str[i++] && quote > 0)
		{
			tmp = ms_expand(str, i);
			get_var(current, tmp, quote, i - 1);
		}
	}
	if (tmp != NULL)
		current->value = tmp;
	else
		current->value = str;
	
}
