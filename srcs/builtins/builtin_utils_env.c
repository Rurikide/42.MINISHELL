/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:04:19 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/22 21:07:18 by tshimoda         ###   ########.fr       */
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
		key_len = env_var_key_len(minishell->env[i]);
		if (key_len == option_len)
		{
			if (ft_strncmp(minishell->env[i], option, key_len) == SUCCESS)
			{
			//	printf("matching key str = %s at index %d\n", minishell->env[i], i);
				return (i);
			}
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
int	env_var_get_key_index(char *key, int size)
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
char	*env_var_get_value(char *key, int size)
{
	// key is the KEY with the '='
	t_minishell *ms;
	int i;
	int match;

	i = 0;
	ms = get_minishell();
	match = env_var_matching_key(key);
//	printf("KEY is %s and size is %d\n", key, size);

	if (match != FAIL)
	{
	//	printf("found a matching key at index %d!!!\n", match);
	//	printf("THE VALUE IS %s\n", &(ms->env[match])[size + 1]);
		// size + 1 pour skipper le '='
		return (&(ms->env[match])[size + 1]);
	}
	// while (ms->env[i] != NULL)
	// {
	// 	//
	// //	printf("\033[1;34mKEY=VALUE is %s \033[0m \n", ms->env[i]);
	// //	printf("env var the value is %s\n\n", &(ms->env[i])[size]);
	
	// 	if (match != FAIL)
	// 	{
	// 		printf("found a matching key at index %d!!!\n", i);
	// 		return (&(ms->env[match])[size]);
	// 	}
	// 		// return the value after the '='
	// 	i++;
	// }
	return (NULL);
}

void	init_shlvl(void)
{
	char	*shlvl;
	int		lvl;
	
	shlvl = env_var_get_value("SHLVL", ft_strlen("SHLVL"));
//	printf("shlvl is %s\n", shlvl);
	if (shlvl == NULL)
		lvl = 1;
	else
	{
	//	printf("dans le else\n");
		lvl = ft_atoi(shlvl) + 1;
	}
//	printf("RESULT lvl= %d\n", lvl);
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