/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:13:05 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/01 12:43:13 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit_error(char **options, int error_nb)
{
	if (error_nb == ERROR_255)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(options[0], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		get_minishell()->exit_nb = ERROR_255;
	}
	else if (error_nb == ERROR_1)
	{
		ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
		ft_putstr_fd(options[0], STDOUT_FILENO);
		ft_putstr_fd(": too many arguments\n", STDOUT_FILENO);
		get_minishell()->exit_nb = ERROR_1;
	}
}

void	builtin_exit(char **options)
{
	long long	nb_options;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (options[0] != NULL)
	{
		nb_options = ft_table_len(options);
		if (ft_is_str_digit_only(options[0]) == FAIL \
		|| ft_isllong(options[0]) == FAIL)
		{
			builtin_exit_error(options, ERROR_255);
		}
		else if (nb_options > 1)
		{
			builtin_exit_error(options, ERROR_1);
		}
		else if (options[0] != NULL)
		{
			nb_options = ft_atoll(options[0]) % 256;
			if (nb_options < 0 || nb_options > 255)
				nb_options = ERROR_255;
			get_minishell()->exit_nb = nb_options;
		}
	}
	free_minishell();
	exit(get_minishell()->exit_nb);
}
