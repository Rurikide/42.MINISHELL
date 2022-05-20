/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:04:19 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/19 22:32:00 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_key_len(char *key)
{
	int	len;

	len = 0;
	while (key[len] != '=' && key[len] != '\0')
	{
		len++;
	}
	return (len);
}

int	env_var_matching_key(char *option)
{
	t_minishell	*minishell;
	int			i;
	int			key_len;
	int			option_len;

	i = 0;
	option_len = env_var_key_len(option);
	minishell = get_minishell();
	while (minishell->env[i] != NULL)
	{
		key_len = env_var_key_len(minishell->env[i]);
		if (key_len == option_len)
		{
			if (ft_strncmp(minishell->env[i], option, key_len) == SUCCESS)
				return (i);
		}
		i++;
	}
	return (FAIL);
}

char	*env_var_get_key_n_value(char *key)
{
	t_minishell	*minishell;
	int			i;

	i = env_var_matching_key(key);
	minishell = get_minishell();
	if (i != FAIL)
		return (minishell->env[i]);
	return (NULL);
}

char	*env_var_get_value(char *key, int size)
{
	t_minishell	*minishell;
	int			i;

	i = env_var_matching_key(key);
	minishell = get_minishell();
	if (i != FAIL)
		return (&(minishell->env[i])[size + 1]);
	return (NULL);
}

int	env_var_is_key_only(char *option)
{
	int	i;
	int	equal;

	i = 0;
	equal = YES;
	while (option[i])
	{
		if (option[i] == '=')
		{
			equal = NO;
			break ;
		}
		i++;
	}
	return (equal);
}
