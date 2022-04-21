/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:15:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/21 17:24:20 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// key == name of the env var; size == len of the env var + 1 for the '='; update == value only to the env var
void	env_var_export_update(char *update, int pos, int new)
{
	t_minishell *minishell;
	char **back_up;
	int nb;

	minishell = get_minishell();
	back_up = minishell->env;
	if (new == NO)
	{
		printf("env_var_export_update pos = %d\n", pos);
		printf("env_var_export_update update = %s\n", minishell->env[pos]);
		free(minishell->env[pos]);
		minishell->env[pos] = ft_strdup(update);
		printf("env_var_export_update pos = %d\n", pos);
		printf("env_var_export_update update = %s\n", minishell->env[pos]);
	}
	else if (new == YES)
	{
		minishell->env_size++;
		minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
		nb = 0;
		while (back_up[nb] != NULL)
		{
			minishell->env[nb] = ft_strdup(back_up[nb]);
			nb++;
		}
		minishell->env[nb] = ft_strdup(update);
		minishell->env[nb + 1] = NULL;
	}
	ft_free_table(back_up);
}

void	env_var_update(char *key, char *update)
{
	int i;

	i = env_var_matching_key(key);
	if (i == FAIL)
		env_var_add(key, update);
	else	
	{
		free(get_minishell()->env[i]);
		get_minishell()->env[i] = ft_strjoin_symbol(key, '=', update);
	}
}

void	env_var_add(char *key, char *update)
{
	t_minishell *minishell;
	char **back_up;
	int nb;
	
	minishell = get_minishell();
	back_up = minishell->env;
	minishell->env_size++;
	minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	nb = 0;
	while (back_up[nb] != NULL)
	{
		minishell->env[nb] = ft_strdup(back_up[nb]);
		nb++;
	}
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
	
	i = 0;
	j = 0;
	minishell = get_minishell();
	minishell->env_size--;
	back_up = minishell->env;
	minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	while (i < minishell->env_size - 1)
	{
		if (i == env_index)
			j++;
		minishell->env[i++] = ft_strdup(back_up[j++]);
	}
	ft_free_table(back_up);
	// Je crois que ce n'est pas nécessaire de mettre un NULL, mais à reverifier
}
