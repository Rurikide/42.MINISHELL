/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:23:57 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/17 15:57:27 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_a_builtin(char **options)
{
	int	is_builtin;

	if (ft_is_a_match("echo", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("cd", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("pwd", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("export", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("unset", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("env", options[0]) == YES)
		is_builtin = YES;
	else if (ft_is_a_match("exit", options[0]) == YES)
		is_builtin = YES;
	else
		is_builtin = NO;
	return (is_builtin);
}
	//ft_free_table(options);

int	execution_builtins(char **options)
{
	int	is_builtin;

	is_builtin = YES;
	if (ft_is_a_match("echo", options[0]) == YES)
		builtin_echo(&options[1], 0);
	else if (ft_is_a_match("cd", options[0]) == YES)
		builtin_cd(&options[1]);
	else if (ft_is_a_match("pwd", options[0]) == YES)
		builtin_pwd(&options[1]);
	else if (ft_is_a_match("export", options[0]) == YES)
		builtin_export(&options[1], 0, 0);
	else if (ft_is_a_match("unset", options[0]) == YES)
		builtin_unset(&options[1], 0);
	else if (ft_is_a_match("env", options[0]) == YES)
		builtin_env(&options[1]);
	else if (ft_is_a_match("exit", options[0]) == YES)
		builtin_exit(&options[1]);
	else
		is_builtin = NO;
	return (is_builtin);
}
