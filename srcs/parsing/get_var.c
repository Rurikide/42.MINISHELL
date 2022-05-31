/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/31 16:55:49 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_str(char *str, char *var, int i, int j)
{
	char	*tmp;

	tmp = ft_substr(str, i, j);
	var = env_var_get_value(tmp, j);
	free(tmp);
	if (var == NULL)
	{
		if (!(ft_isprint(str[i])) || str[i] == ' ')
			var = "$";
		else
			var = "";
	}
	return (var);
}

void	get_var_question_mark(char *str, char *var, int *i, int *j)
{
	if (str[*i] == '?')
	{
		free(var);
		*j += 1;
	}
	*i += *j;
}

char	*get_var_heredoc_str(char *str, int i, int j)
{
	char	*var;

	var = NULL;
	if (str[i + j] == '?')
		var = ft_itoa(get_minishell()->exit_nb);
	else
		var = get_var_str(str, var, i, j);
	if (var == NULL)
	{
		if (!(ft_isprint(str[i])) || str[i] == ' ')
			var = "$";
		else
			var = "";
	}
	return (var);
}

char	*get_var_heredoc(char *str, int quote, int i, int j)
{
	char	*var;
	char	*tmp;
	int		k;
	int		l;

	tmp = ft_calloc(ft_strlen(str) + get_length(str, -1, 0, 0) + 1, \
	sizeof(char));
	initialize_zero(&i, &j, &l);
	while (str[i])
	{
		if (str[i] == '\'')
			quote *= -1;
		if (str[i] == '$' && quote > 0)
		{
			reset_i_j_k(&i, &j, &k);
			get_var_skip_sp_char(str, i, &j);
			var = get_var_heredoc_str(str, i, j);
			while (var[k])
				tmp[l++] = var[k++];
			get_var_question_mark(str, var, &i, &j);
		}
		else
			tmp[l++] = str[i++];
	}
	return (tmp);
}

void	get_var(t_node *current, char *str, int quote, int i)
{
	char	*var;
	int		j;
	int		k;
	int		l;

	initialize_zero(&i, &j, &l);
	while (str[i])
	{
		if (str[i] == '\'')
			quote *= -1;
		if (str[i] == '$' && quote > 0)
		{
			reset_i_j_k(&i, &j, &k);
			get_var_skip_sp_char(str, i, &j);
			if (str[i + j] == '?')
				var = ft_itoa(get_minishell()->exit_nb);
			else
				var = get_var_str(str, var, i, j);
			while (var[k])
				current->value[l++] = var[k++];
			get_var_question_mark(str, var, &i, &j);
		}
		else
			current->value[l++] = str[i++];
	}
}

/*static char	*ms_expand(char *str, int i)
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
	
}*/
