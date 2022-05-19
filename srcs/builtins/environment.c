/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:23:19 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/19 14:41:34 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	init_shlvl(void)
{
	char	*shlvl;
	int		lvl;

	shlvl = env_var_get_value("SHLVL", ft_strlen("SHLVL"));
	if (shlvl == NULL)
		lvl = 1;
	else
		lvl = ft_atoi(shlvl) + 1;
	shlvl = ft_itoa(lvl);
	env_var_update("SHLVL", shlvl);
	free(shlvl);
}

void	init_env(char **env)
{
	t_minishell	*minishell;
	int			nb;

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
	minishell->env[nb] = NULL;
	init_shlvl();
}
// IMPORTANT METTRE NULL avant la fonction init_shlvl
