/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:13:07 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/25 10:57:39 by tshimoda         ###   ########.fr       */
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
			printf("i = %d and str = %s\n", i, minishell->env[i]);
			//ft_putendl_fd(minishell->env[i], STDOUT_FILENO);
		i++;
	}
}

void	env_var_print_quotes(char **table, int i, int j, int equal)
{
	while (table[i] != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = 0;
		equal = NO;
		while (table[i][j] != '\0')
		{
			ft_putchar_fd(table[i][j], STDOUT_FILENO);
			if (table[i][j] == '=')
			{
				equal = YES;
				ft_putchar_fd('\"', STDOUT_FILENO);
			}
			j++;
			if (table[i][j] == '\0')
			{
				if (equal == YES)
					ft_putchar_fd('\"', STDOUT_FILENO);
				ft_putchar_fd('\n', STDOUT_FILENO);
			}
		}
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
	env_var_print_quotes(table, 0, 0, NO);
	ft_free_table(table);
}
