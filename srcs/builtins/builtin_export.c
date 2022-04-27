/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:15:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/27 16:52:30 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

int	evaluate_export_type(char *option)
{
	int i;
	int equal;

	i = 1;
	equal = NO;
	// TYPEFAIL INVALID KEY, TYPE1: KEY ONLY,    TYPE2: KEY=,  TYPE3: KEY=VALUE
	if (!ft_isalpha(option[0]) && option[0] != '_')
		return (FAIL);
	while (option[i])
	{
		// IF THERE IS AN EQUAL SYMBOL
		if (option[i] == '=')
		{
			equal = YES;
			if (option[i + 1] == '\0')
				return (2);
			else 
			{
				// if 	(env_var_valid_value(&option[i], 0, 0) == FAIL)
				// 	return (FAIL);
				return (3);
			}
		}
		if (!ft_isalnum(option[i]) && option[i] != '_' && equal == NO)
			return (FAIL);
		if (option[i] == '/' && equal == NO)
			return(FAIL);
		i++;
	}
	return(1);
}

void	builtin_export(char **options)
{
	int i;
	int type;
	int pos;

	i = 0;
	get_minishell()->exit_nb = SUCCESS;
	if (options[i] == NULL)
	{
		env_var_print_in_order(get_minishell(), 0, 0);
		return ;
	}
	while (options[i])
	{
		// TYPE1: KEY ONLY    TYPE2: KEY=  TYPE3: KEY=VALUE
		type = evaluate_export_type(options[i]);
		if (type == FAIL)
		{
			printf("export: `%s': not a valid identifier\n", options[i]);
			get_minishell()->exit_nb = ERROR_1;
		}
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

// POOURRQUOI   ./minishell "export type=shadoow TERM= ZSH=ciaobye LESS _=/R" ??? le dernier print avant le type=shadoow