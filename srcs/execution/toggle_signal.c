/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:22:46 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/17 15:24:47 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
