/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:15:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/19 19:08:54 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_var_export_update(char *update, int pos, int new)
{
	t_minishell	*minishell;

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

void	env_var_update(char *key, char *update)
{
	t_minishell	*minishell;
	int			nb;

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

// void	env_var_add(char *key, char *update)
// {
// 	t_minishell	*minishell;
// 	 char		**back_up;
// 	//char		*str;

// 	minishell = get_minishell();
// 	minishell->env_size++;
// //	str = ft_strjoin_symbol(key, '=', update);;
// 	back_up= ft_table_add(minishell->env, update);
// 	//free(str);
// 	// ft_free_table(minishell->env);
// 	minishell->env = back_up;
// 	minishell->env[ft_table_len(back_up)] = ft_strjoin_symbol(key, '=', update);
// 	minishell->env[ft_table_len(back_up) + 1] = NULL;
// }
// //ft_free_table(back_up);

void	env_var_del(int env_index)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	minishell->env_size--;
	ft_table_del(minishell->env, env_index);
}

void	env_var_add(char *key, char *update)
{
	t_minishell	*minishell;
	char		*str;

	minishell = get_minishell();
	minishell->env_size++;
	str = ft_strjoin_symbol(key, '=', update);
	minishell->env = ft_table_add(minishell->env, str);
	free(str);
}
