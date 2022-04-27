/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:13:07 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/27 16:52:44 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_minishell(void)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	if (minishell->env != NULL)
		ft_free_table(minishell->env);
	if (minishell->options != NULL)
		ft_free_table(minishell->options);
	if (minishell->user_input != NULL)
		free(minishell->user_input);
	rl_clear_history();
}

t_answer	ft_is_a_match(char *keyword, char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	if (input == NULL)
		return (NO);
	if (ft_strlen(keyword) != ft_strlen(input))
		return (NO);
	while (i < len)
	{
		if (keyword[i] == input[i])
			i++;
		else
			return (NO);
	}
	return (YES);
}

t_answer	ft_is_option(char valid, char *list)
{
	size_t	i;

	i = 0;
	if (list[i] == '\0')
		return (NO);
	while (list[i] != '\0')
	{
		if (valid == list[i])
			i++;
		else
			return (NO);
	}
	return (YES);
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
