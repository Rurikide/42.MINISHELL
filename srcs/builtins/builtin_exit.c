/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:13:05 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/09 17:49:25 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    builtin_exit(t_node *current, char **options)
{
	long long nb_options;

	ft_putendl_fd("exit", current->fd_o);
	if (options[0] != NULL)
	{
		nb_options = ft_table_len(options);
		if (ft_is_str_digit_only(options[0]) == FAIL || ft_isllong(options[0]) == FAIL)
		{
			ft_putstr_fd("minishell: exit:", current->fd_o);
			ft_putstr_fd(options[0], current->fd_o);
			ft_putstr_fd(": numeric argument required\n", current->fd_o);

			//printf("minishell: exit: %s: numeric argument required\n", options[0]);
			get_minishell()->exit_nb = ERROR_255;
		}
		else if (nb_options > 1)
		{
			ft_putstr_fd("minishell: exit:", current->fd_o);
			ft_putstr_fd(options[0], current->fd_o);
			ft_putstr_fd(": too many arguments\n", current->fd_o);
			//printf("minishell: exit: %s: too many arguments\n", options[0]);
			get_minishell()->exit_nb = ERROR_1;
		}
		else if (options[0] != NULL)
		{
			nb_options = ft_atoll(options[0]) % 256;
			if (nb_options < 0 || nb_options > 255)
				nb_options = ERROR_255;
			get_minishell()->exit_nb = nb_options;
		}
	}
	// VERIFIER les exit code de CTRL-C et D
//	printf("EXIT NB = %d\n", get_minishell()->exit_nb);
	//
	free_minishell();
	exit(get_minishell()->exit_nb);
}
