/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:04:19 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/16 17:11:31 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
	option_len = env_var_key_len(option);
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

// function return the whole env var. ex HOME=usr/
char	*env_var_get_key_value(char *key)
{
	// key is just the KEY no '='
	t_minishell *ms;

	ms = get_minishell();

	if (*ms->env == NULL)
		return (NULL);

	while (*ms->env != NULL)
	{
		//printf("whats the key ? %s\n", key);
		if (env_var_matching_key(key) == SUCCESS)
		//if (ft_strncmp(*ms->env, key, size) == SUCCESS)
		{
			//printf("%s\n", *ms->env);
			return (*ms->env);
		}
		else
			ms->env++;
	}
	return (NULL);
}

// function returns the index position of the env var a.k.a key
int	env_var_get_key_index(char *key, size_t size)
{
	t_minishell *ms;
	int		i;

	i = 0;
	ms = get_minishell();
	while (ms->env[i] != NULL)
	{
		if (ft_strncmp(ms->env[i], key, size) == SUCCESS)
			return (i);
		i++;
	}
	return (FAIL);
}

// function retrieves the value of the key env m
char	*env_var_get_value(char *key, size_t size)
{
	// key is the KEY with the '='
	t_minishell *ms;

	ms = get_minishell();

	if (ms->env == NULL)
		return (NULL);

	while (ms->env != NULL)
	{
		if (ft_strncmp(*ms->env, key, size) == SUCCESS)
			return (&(*ms->env)[size]);
			// return the value after the '='
		else
			ms->env++;
	}
	return (NULL);
}

// function allocates memory for minishell->env and strdup the env from the main
void	init_env(char **env)
{
	t_minishell *minishell;
	size_t nb;

	nb = 0;
	while (env[nb] != NULL)
		nb++;
	minishell = get_minishell();
	minishell->env_size = nb + 1;
	minishell->env = ft_calloc((nb + 1), sizeof(char *));
	nb = 0;
	while (env[nb] != NULL)
	{
		minishell->env[nb] = ft_strdup(env[nb]);
		nb++;
	}
	env_var_update("SHLVL", ft_itoa(minishell->shlvl));
	
	minishell->env[nb] = NULL;
}