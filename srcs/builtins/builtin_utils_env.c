/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:04:19 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/25 12:35:04 by adubeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// len of the KEY only, not KEY=VALUE
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

// returns the index position of the matching key
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
		//printf("matching key str = %s\n", minishell->env[i]);
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
	int i;

	i = 0;
	ms = get_minishell();
	while (ms->env[i] != NULL)
	{
		//printf("whats the key ? %s\n", key);
		if (env_var_matching_key(key) == SUCCESS)
		//if (ft_strncmp(*ms->env, key, size) == SUCCESS)
		{
			//printf("%s\n", *ms->env);
			return (ms->env[i]);
		}
		else
			i++;
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
char	*env_var_get_value(char *key, int	size)
{
	// key is the KEY with the '='
	t_minishell	*minishell;
	int			i;

	i = env_var_matching_key(key);
	minishell = get_minishell();
	if (i != FAIL)
		return (&(minishell->env[i])[size + 1]);
	return (NULL);
}

void	init_shlvl(void)
{
	char	*shlvl;
	int		lvl;
	
	shlvl = env_var_get_value("SHLVL=", 6);
	if (shlvl == NULL)
		lvl = 1;
	else
		lvl = (ft_atoi(shlvl) + 1);
	shlvl = ft_itoa(lvl);
	env_var_update("SHLVL", shlvl);
	free(shlvl);
}

// function allocates memory for minishell->env and strdup the env from the main
void	init_env(char **env)
{
	t_minishell *minishell;
	int nb;

	nb = 0;
	while (env[nb] != NULL)
		nb++;
	minishell = get_minishell();
	minishell->env_size = nb + 1;
	minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	nb = 0;
	while (env[nb] != NULL)
	{
		minishell->env[nb] = ft_strdup(env[nb]);
		nb++;
	}
	// IMPORTANT METTRE NULL avant la fonction init_shlvl
	minishell->env[nb] = NULL;
	init_shlvl();
}
