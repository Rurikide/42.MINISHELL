/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:36:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/03 16:52:50 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_i_j_k(int *i, int *j, int *k)
{
	*i += 1;
	*j = 0;
	*k = 0;
}

void	initialize_zero(int *i, int *j, int *l)
{
	*i = 0;
	*j = 0;
	*l = 0;
}

	//if (ft_strlen(str) == i || str[i] == ' ')
void	get_length_core(char *str, int i, int *j, int *k)
{
	char	*var;
	char	*tmp;

	while (str[i + *j] && str[i + *j] != ' ' && str[i + *j] != '$' && \
	str[i + *j] != '?' && str[i + *j] != '"' && str[i + *j] != '\'')
		*j += 1;
	if (str[i + *j] == '?')
		var = ft_itoa(get_minishell()->exit_nb);
	else
	{
		tmp = ft_substr(str, i, *j);
		var = env_var_get_value(tmp, *j);
		free(tmp);
	}
	if (!(ft_isprint(str[i])) || str[i] == ' ')
		var = "$";
	if (var == NULL)
		return ;
	while (var[*k])
		*k += 1;
	if (str[i] == '?')
	{
		free(var);
		*j += 1;
	}
}

int	get_length(char *str, int i, int j, int k)
{
	int		c;
	int		quote;
	int		len;

	c = 0;
	quote = 1;
	len = ft_strlen(str);
	if (len == 0)
		return (0);
	while (str[++i])
	{
		if (str[i] == '\'')
			quote *= -1;
		if (str[i] == '$' && quote > 0)
		{
			reset_i_j_k(&i, &j, &k);
			get_length_core(str, i, &j, &k);
			c += k - j - 1;
		}
	}
	return (c);
}

void	get_var_skip_sp_char(char *str, int i, int *j)
{
	while (str[i + *j] && str[i + *j] != ' ' && str[i + *j] != '$' && \
	str[i + *j] != '?' && str[i + *j] != '"' && str[i + *j] != '\'')
		*j += 1;
}
