/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:01:06 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/17 15:02:25 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_minishell	*get_minishell(void)
{
	static t_minishell	minishell;

	if (minishell.init != 1)
	{
		minishell.init = 1;
		minishell.shlvl = 1;
		minishell.env = NULL;
		minishell.env_size = 0;
		minishell.exit_nb = 0;
		minishell.user_input = NULL;
		minishell.options = NULL;
		minishell.head = NULL;
	}
	return (&minishell);
}

void	free_minishell(void)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	if (minishell->env != NULL)
		ft_free_table(minishell->env);
	if (minishell->options != NULL)
		ft_free_table(minishell->options);
	if (minishell->user_input != NULL)
		free(minishell->user_input);
	rl_clear_history();
}