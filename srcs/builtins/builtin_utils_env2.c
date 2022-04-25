/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:15:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/25 11:30:37 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// key == name of the env var; size == len of the env var + 1 for the '='; update == value only to the env var
void	env_var_export_update(char *update, int pos, int new)
{
	t_minishell *minishell;
	char **back_up;
	int nb;
	
	nb = -1;
	minishell = get_minishell();
	back_up = ft_calloc(minishell->env_size, sizeof(char *));
	while (minishell->env[++nb] != NULL)
		back_up[nb] = ft_strdup(minishell->env[nb]);
	if (new == NO)
	{
		free(minishell->env[pos]);
		minishell->env[pos] = ft_strdup(update);
	}
	else if (new == YES)
	{
		minishell->env_size++;
		minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
		nb = -1;
		while (back_up[++nb] != NULL)
			minishell->env[nb] = ft_strdup(back_up[nb]);
		minishell->env[nb] = ft_strdup(update);
		minishell->env[nb + 1] = NULL;
	}
	ft_free_table(back_up);
}

void	env_var_update(char *key, char *update)
{
	int nb;

	nb = env_var_matching_key(key);
	if (nb == FAIL)
		env_var_add(key, update);
	else	
	{
		free(get_minishell()->env[nb]);
		get_minishell()->env[nb] = ft_strjoin_symbol(key, '=', update);
	}
}

void	env_var_add(char *key, char *update)
{
	t_minishell *minishell;
	char **back_up;
	int nb;
	
	minishell = get_minishell();
	minishell->env_size++;

	nb = -1;
	back_up = ft_calloc(minishell->env_size, sizeof(char *));
	while (minishell->env[++nb] != NULL)
		back_up[nb] = ft_strdup(minishell->env[nb]);
	minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	nb = -1;
	while (back_up[++nb] != NULL)
		minishell->env[nb] = ft_strdup(back_up[nb]);
	minishell->env[nb] = ft_strjoin_symbol(key, '=', update);
	minishell->env[nb + 1] = NULL;
	ft_free_table(back_up);
}

void	env_var_del(int env_index)
{
	t_minishell *minishell;
	char **back_up;
	int i;
	int j;
	
	minishell = get_minishell();
	minishell->env_size--;
	i = -1;
	back_up = ft_calloc(minishell->env_size + 1, sizeof(char *));
	while (minishell->env[++i] != NULL)
		back_up[i] = ft_strdup(minishell->env[i]);
	i = 0;
	j = 0;
	minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	while (i < minishell->env_size - 1)
	{
		if (i == env_index)
			j++;
		minishell->env[i++] = ft_strdup(back_up[j++]);
	}
	minishell->env[i] = NULL;
	ft_free_table(back_up);
}
