/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:13:07 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/23 16:17:03 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_var_print(void)
{
	t_minishell	*minishell;
	int			i;

	i = 0;
	minishell = get_minishell();
	while (minishell->env[i] != NULL)
	{
		if (env_var_is_key_only(minishell->env[i]) == NO)
			printf("%s\n", minishell->env[i]);
		i++;
	}
}

void	env_var_print_in_order(t_minishell *ms, int i, int j)
{
	char	**table;

	table = ft_calloc(ms->env_size, sizeof(char *));
	while (ms->env[i] != NULL)
	{
		table[i] = ft_strdup(ms->env[i]);
		i++;
	}
	i = 0;
	while (ms->env[i] != NULL)
	{
		j = i + 1;
		while (table[j] != NULL)
		{
			if (ft_strcmp(table[i], table[j]) > 0)
				ft_swap(&table[i], &table[j]);
			j++;
		}
		i++;
	}
	table[i] = NULL;
	i = 0;
	while (table[i])
		printf("%s\n", table[i++]);
	ft_free_table(table);
}
