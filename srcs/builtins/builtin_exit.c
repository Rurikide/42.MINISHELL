/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:13:05 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/25 16:05:24 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_minishell(void)
{
	t_minishell *minishell;
	
	minishell = get_minishell();
	if (minishell->env != NULL)
		ft_free_table(minishell->env);
	if (minishell->options != NULL)
	   ft_free_table(minishell->options);
	if (minishell->user_input != NULL)
		free(minishell->user_input);
	rl_clear_history();
}

void    builtin_exit(char **options)
{
	long long nb_options;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (options[0] != NULL)
	{
		nb_options = ft_table_len(options);
		if (ft_is_str_digit_only(options[0]) == FAIL || ft_isllong(options[0]) == FAIL)
		{
			printf("minishell: exit: %s: numeric argument required\n", options[0]);
			get_minishell()->exit_nb = ERROR_255;
		}
		else if (nb_options > 1)
		{
			printf("minishell: exit: %s: too many arguments\n", options[0]);
			get_minishell()->exit_nb = ERROR_1;
		}
		else if (options[0] != NULL)
		{
			nb_options = ft_atoll(options[0]) % 256;
			if (nb_options < 0 || nb_options > 255)
				nb_options = ERROR_255;
			// printf("options[0] = %s and atoll result = %lld\n", options[0], nb_options);
			get_minishell()->exit_nb = nb_options;
		}
	}
	printf("EXIT NB = %d\n", get_minishell()->exit_nb);
	free_minishell();
	exit(get_minishell()->exit_nb);
}
