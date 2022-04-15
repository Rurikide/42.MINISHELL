/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:15:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/15 17:11:07 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// key == name of the env var; size == len of the env var + 1 for the '='; update == value only to the env var

 // function updating an env var
 // env_var_update must receive the key followed by a '=' for the ft_strjoin
void	env_var_update(char *key, size_t size, char *update)
{
	int i;

	i = 0;

	// FAIRE UN CHECK SI LA VARIABLE NEXISTE PAS
	i = env_var_get_key_index(key, size);
	if (i == FAIL)
		env_var_add(key, size, update);
	else	
		get_minishell()->env[i] = ft_strjoin(key, update);
}

// function who adds a new env var
void	env_var_add(char *key, size_t size, char *update)
{
	t_minishell *minishell;
	char **back_up;
	int nb;
	
	nb = 0;
	back_up = minishell->env;
	minishell = get_minishell();
	minishell->env_size++;
	minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	while (nb < minishell->env_size - 1)
	{
		minishell->env[nb] = ft_strdup(back_up[nb]);
		nb++;
	}
	minishell->env[nb] = ft_strjoin(key, update);
}

void	env_var_del(char *key, int env_index)
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


int	env_var_key_len(char *key)
{
	int	len;

	len = 0;
	while (key[len] != '=' && key[len] != '\0')
	{
		len++;
	}
	return (len);
}

int	env_var_matching_key(char *option)
{
	t_minishell	*minishell;
	int			i;
	int			key_len;
	int			option_len;

	i = 0;
	option_len = ft_strlen(option);
	minishell = get_minishell();
	while (minishell->env[i] != NULL)
	{
		key_len = env_var_key_len(minishell->env[i]);
		if (key_len == option_len)
		{
			if (ft_strncmp(minishell->env[i], option, key_len) == SUCCESS)
				return (i);
		}
		i++;
	}
	return (FAIL);
}
