/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:15:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/19 14:46:39 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_var_print_quotes(char **table, int equal, int i, int j)
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
	env_var_print_quotes(table, NO, 0, 0);
	ft_free_table(table);
}

// TYPEFAIL INVALID KEY, TYPE1: KEY ONLY,    TYPE2: KEY=,  TYPE3: KEY=VALUE
int	evaluate_export_type(char *option)
{
	int	equal;
	int	i;

	i = 1;
	equal = NO;
	if (!ft_isalpha(option[0]) && option[0] != '_')
		return (FAIL);
	while (option[i])
	{
		if (option[i] == '=')
		{
			equal = YES;
			if (option[i + 1] == '\0')
				return (2);
			else
				return (3);
		}
		if (!ft_isalnum(option[i]) && option[i] != '_' && equal == NO)
			return (FAIL);
		if (option[i] == '/' && equal == NO)
			return (FAIL);
		i++;
	}
	return (1);
}

void	builtin_export_invalid_key(char **options, int i)
{
	ft_putstr_fd(MINISHELL, STDOUT_FILENO);
	ft_putstr_fd("export: `", STDOUT_FILENO);
	ft_putstr_fd(options[i], STDOUT_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
	get_minishell()->exit_nb = ERROR_1;
}

void	builtin_export(char **options, int type, int i)
{
	int	pos;

	get_minishell()->exit_nb = SUCCESS;
	if (options[i] == NULL)
	{
		env_var_print_in_order(get_minishell(), 0, 0);
		return ;
	}
	while (options[i])
	{
		type = evaluate_export_type(options[i]);
		if (type == FAIL)
			builtin_export_invalid_key(options, i);
		else
		{
			pos = env_var_matching_key(options[i]);
			if ((type == 2 || type == 3) && pos != FAIL)
				env_var_export_update(options[i], pos, NO);
			else if ((type == 2 || type == 3) && pos == FAIL)
				env_var_export_update(options[i], pos, YES);
			else if (type == 1 && pos == FAIL)
				env_var_export_update(options[i], pos, YES);
		}
		i++;
	}
}
