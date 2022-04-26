/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:15:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/26 18:28:36 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**ft_table_deepcopy(char **table, const char *new)
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

void	ft_table_remove(char **table, int index)
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

// key == name of the env var; size == len of the env var + 1 for the '='; update == value only to the env var
void	env_var_export_update(char *update, int pos, int new)
{
	t_minishell *minishell;
	//char **back_up;
	//int nb;
	
	//
	printf("inside env_var_export_update\n");
	//
	minishell = get_minishell();
	// back_up = ft_calloc(minishell->env_size, sizeof(char *));
	// nb = -1;
	// while (minishell->env[++nb] != NULL)
	// {
	// 	printf("[%d] minienv %s\n", nb, minishell->env[nb]);
	// 	back_up[nb] = ft_strdup(minishell->env[nb]);
	// }
	// printf("[%d] minienv %s\n", nb, minishell->env[nb]);
	// back_up[nb] = NULL;;
	if (new == NO)
	{
		free(minishell->env[pos]);
		minishell->env[pos] = ft_strdup(update);
	}
	else if (new == YES)
	{
		minishell->env_size++;
		minishell->env = ft_table_deepcopy(minishell->env, update);
		// minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
		// nb = -1;
		// while (back_up[++nb] != NULL)
		// {
		// 	printf("[%d] back_up_env %s\n", nb, back_up[nb]);
		// 	minishell->env[nb] = ft_strdup(back_up[nb]);
		// }
		// printf("[%d] back_up_env %s\n", nb, back_up[nb]);
		// minishell->env[nb] = ft_strdup(update);
		// minishell->env[nb + 1] = NULL;
	}
	//ft_free_table(back_up);
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
	//int nb;
	
	//
	printf("inside env_var_ADD\n");
	//

	minishell = get_minishell();
	minishell->env_size++;
	// back_up = ft_calloc(minishell->env_size, sizeof(char *));
	// nb = -1;
	// while (minishell->env[++nb] != NULL)
	// 	back_up[nb] = ft_strdup(minishell->env[nb]);
	// back_up[nb] = NULL;
	back_up = ft_table_deepcopy(minishell->env, update);
	ft_free_table(minishell->env);
	// minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	minishell->env = back_up;
	// nb = -1;
	// while (back_up[++nb] != NULL)
	// 	minishell->env[nb] = ft_strdup(back_up[nb]);
	minishell->env[ft_table_len(back_up)] = ft_strjoin_symbol(key, '=', update);
	minishell->env[ft_table_len(back_up) + 1] = NULL;
	//ft_free_table(back_up);
}

void	env_var_del(int env_index)
{
	t_minishell *minishell;
	char **back_up;
	int i;
	int j;
	
		//
	printf("inside env_var_DEL\n");
	//

	minishell = get_minishell();
	minishell->env_size--;
	i = -1;
	back_up = ft_calloc(minishell->env_size + 1, sizeof(char *));
	while (minishell->env[++i] != NULL)
		back_up[i] = ft_strdup(minishell->env[i]);
	back_up[i] = NULL;
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
