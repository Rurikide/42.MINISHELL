/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:15:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/16 17:40:52 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// key == name of the env var; size == len of the env var + 1 for the '='; update == value only to the env var

void	env_var_export_update(char *update, int pos, int new)
{
	t_minishell *minishell;
	char **back_up;
	int nb;

	nb = 0;
	minishell = get_minishell();
	back_up = minishell->env;
	if (new == NO)
	{
		minishell->env[pos] = ft_strdup(update);
	}
	else if (new == YES)
	{
		minishell->env_size++;
		minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
		while (nb < minishell->env_size - 1)
		{
			minishell->env[nb] = ft_strdup(back_up[nb]);
			nb++;
		}
		minishell->env[nb - 1] = ft_strdup(update);
	}
}

void	env_var_update(char *key, char *update)
{
	int i;

	i = 0;

	// FAIRE UN CHECK SI LA VARIABLE NEXISTE PAS
	//i = env_var_get_key_index(key, size);
	i = env_var_matching_key(key);
	if (i == FAIL)
		env_var_add(key, update);
	else	
		get_minishell()->env[i] = ft_strjoin_symbol(key, '=', update);
}

// function who adds a new env var
void	env_var_add(char *key, char *update)
{
	t_minishell *minishell;
	char **back_up;
	int nb;
	
	nb = 0;
	minishell = get_minishell();
	back_up = minishell->env;
	minishell->env_size++;
	minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	while (nb < minishell->env_size - 1)
	{
		minishell->env[nb] = ft_strdup(back_up[nb]);
		nb++;
	}
	minishell->env[nb] = ft_strjoin_symbol(key, '=', update);
}

void	env_var_del(int env_index)
{
	t_minishell *minishell;
	char **back_up;
	int i;
	int j;
	
	i = 0;
	j = 0;
	minishell = get_minishell();
	minishell->env_size--;
	back_up = minishell->env;
	// ft_free_table(minishell->env);
	// free(minishell->env);
	minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	while (i < minishell->env_size - 1)
	{
		if (i == env_index)
			j++;
		minishell->env[i++] = ft_strdup(back_up[j++]);
	}
	// Je crois que ce n'est pas nécessaire de mettre un NULL, mais à reverifier
}
