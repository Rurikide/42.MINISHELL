/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:01:06 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/31 14:47:10 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		minishell.is_heredoc = NO;
		minishell.options = NULL;
		minishell.home = NULL;
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
	if (minishell->user_input != NULL)
		free(minishell->user_input);
	if (minishell->options != NULL)
		ft_free_table(minishell->options);
	if (minishell->head != NULL)
		ms_free_list(minishell->head);
	rl_clear_history();
}

void	mini_free_options(char **options)
{
	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	ft_putstr_fd(*options, STDERR_FILENO);
	ft_free_table(options);
}
