/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:15:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/27 16:59:01 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**ft_table_add(char **table, const char *new)
{
	char **deepcopy;
	int i;

	i = -1;
	deepcopy = ft_calloc(ft_table_len(table) + 2, sizeof(char *));
	if (deepcopy == NULL)
		return (NULL);
	while (table[++i] != NULL)
		deepcopy[i] = ft_strdup(table[i]);
	deepcopy[i] = ft_strdup(new);
	deepcopy[i + 1] = NULL;
	ft_free_table(table);
	return (deepcopy);
}

void	ft_table_del(char **table, int index)
{
	if (index >= ft_table_len(table))
		return ;
	free(table[index]);
	while (table[index] != NULL)
	{
		table[index] = table[index + 1];
		index++;
	}
}

void	env_var_export_update(char *update, int pos, int new)
{
	t_minishell *minishell;

	minishell = get_minishell();
	if (new == NO)
	{
		free(minishell->env[pos]);
		minishell->env[pos] = ft_strdup(update);
	}
	else if (new == YES)
	{
		minishell->env_size++;
		minishell->env = ft_table_add(minishell->env, update);
	}
}

// used in builtin_unset
void	env_var_update(char *key, char *update)
{
	t_minishell	*minishell;
	int nb;

	minishell = get_minishell();
	nb = env_var_matching_key(key);
	if (nb == FAIL)
		env_var_add(key, update);
	else	
	{
		free(get_minishell()->env[nb]);
		minishell->env[nb] = ft_strjoin_symbol(key, '=', update);
	}
}

// VERIFIER SI ENV_VAR_ADD leaks!
void	env_var_add(char *key, char *update)
{
	t_minishell *minishell;
	char		**back_up;

	minishell = get_minishell();
	minishell->env_size++;
	back_up = ft_table_add(minishell->env, update);
	ft_free_table(minishell->env);
	minishell->env = back_up;
	minishell->env[ft_table_len(back_up)] = ft_strjoin_symbol(key, '=', update);
	minishell->env[ft_table_len(back_up) + 1] = NULL;
}
//ft_free_table(back_up);

void	env_var_del(int env_index)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	minishell->env_size--;
	ft_table_del(minishell->env, env_index);
}
