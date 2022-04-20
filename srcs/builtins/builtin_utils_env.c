/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:04:19 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/20 17:38:19 by tshimoda         ###   ########.fr       */
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
char	*env_var_get_value(char *key, size_t size)
{
	// key is the KEY with the '='
	t_minishell *ms;
	int i;

	i = 0;
	ms = get_minishell();
	while (ms->env[i] != NULL)
	{
		if (ft_strncmp(ms->env[i], key, size) == SUCCESS)
			return (&(ms->env[i])[size]);
			// return the value after the '='
		else
			i++;
	}
	return (NULL);
}

// function allocates memory for minishell->env and strdup the env from the main
void	init_env(char **env)
{
	t_minishell *minishell;
	int nb;
	char *shlvl;
	int lvl;

	nb = 0;
	while (env[nb] != NULL)
	{
		// printf("\033[1;32m before nb = %d str =  %s \033[0m \n", nb, env[nb]);
		nb++;
	}
	printf("AAA nb = %d\n", nb);
	minishell = get_minishell();
	minishell->env_size = nb + 1;
	printf("\033[1;32m init env_size == %d \033[0m \n", minishell->env_size);
	minishell->env = ft_calloc(minishell->env_size, sizeof(char *));
	nb = 0;
	while (env[nb] != NULL)
	{
		minishell->env[nb] = ft_strdup(env[nb]);
		printf("\033[1;36m init env nb = %d str = %s \033[0m \n", nb, env[nb]);
		printf("\033[1;34m init env nb = %d str = %s \033[0m \n", nb, minishell->env[nb]);
		nb++;
	}
	minishell->env[nb] = NULL;
	printf("BBB nb = %d\n", nb);
	
	shlvl = env_var_get_value("SHLVL=", 6);
	if (shlvl == NULL)
	{
		//printf("SHLVL is NULL\n");
		lvl = 1;
	}
	else
		lvl = (ft_atoi(shlvl) + 1);
	shlvl = ft_itoa(lvl);
//	printf("shlvl= %s\n", shlvl);
	env_var_update("SHLVL", shlvl);
	free(shlvl);
	minishell->env[nb] = NULL;
}