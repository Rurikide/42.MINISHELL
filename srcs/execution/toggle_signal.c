/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:22:46 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/01 13:37:35 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mute_signals(void)
{
	signal(SIGINT, &void_signal);
	signal(SIGQUIT, &void_signal);
}

void	set_signals(void)
{
	signal(SIGINT, &ctrl_c_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	set_exit_nb(int wstatus)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		minishell->exit_nb = SIG_CTRL_D;
	}
	else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		minishell->exit_nb = SIG_CTRL_C;
	}
	else if (WIFEXITED(wstatus))
	{
		minishell->exit_nb = WEXITSTATUS(wstatus);
	}
	else
	{
		minishell->exit_nb = ERROR_1;
	}
}
