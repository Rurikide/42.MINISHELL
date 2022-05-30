/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:00:31 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/30 12:57:52 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo_empty(void)
{
	write(STDOUT_FILENO, "\n", 1);
	get_minishell()->exit_nb = SUCCESS;
}

void	builtin_echo_exit_nb(char **options, int i)
{
	ft_putstr_fd(ft_itoa(get_minishell()->exit_nb), STDOUT_FILENO);
	if (options[i][2] != '\0')
		write(STDOUT_FILENO, &options[i][2], ft_strlen(&options[i][2]));
}

// void	builtin_echo_tilde(char **options, int i)
// {

// 	// ne pas mettre de backslash n
	
// 	// ft_putstr_fd(ft_itoa(get_minishell()->exit_nb), STDOUT_FILENO);
// 	// if (options[i][2] != '\0')
// 	// 	write(STDOUT_FILENO, &options[i][2], ft_strlen(&options[i][2]));
// }

void	builtin_echo_echo(char **options, int i)
{
	while (options[i] != NULL)
	{
		if (options[i][0] == '$' && options[i][1] == '?')
			builtin_echo_exit_nb(options, i);
		else if (options[i][0] == '~' && options[i][1] == '\0')
		{
		//	builtin_echo_tilde(options, i);
			return ;
		}
		else if (options[i][0] == '~' && (options[i][1] == '\\' || options[i][2] == '\0'))
		{
		//	builtin_echo_tilde(options, i);
			return ;
		}
		else
			write(STDOUT_FILENO, options[i], ft_strlen(options[i]));
		if (options[++i] != NULL)
			write(1, " ", 1);
	}
}

void	builtin_echo(char **options, int i)
{
	t_answer	remove_nl;

	remove_nl = NO;
	if (*options == NULL)
	{
		builtin_echo_empty();
		return ;
	}
	while (options[i] != NULL && *options[i] == '-')
	{
		if (ft_is_option('n', &(options[i])[1]) == YES)
			remove_nl = YES;
		else
			break ;
		i++;
	}
	builtin_echo_echo(options, i);
	if (remove_nl == NO)
		write(STDOUT_FILENO, "\n", 1);
	get_minishell()->exit_nb = SUCCESS;
}
