/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:00:31 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/12 11:42:59 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// bash behaviour : can receive multiple -n -n -n -nnnnnnnn options
// which remove the newline. If there is no -n as the first option, 
// it will treat the everything as text input.
// this function receive the array after the echo.
void	builtin_echo(t_node *current, char **options)
{
	t_answer	remove_nl;
	int			i;

	i = 0;
	remove_nl = NO;
	if (*options == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		get_minishell()->exit_nb = SUCCESS;
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
	while (options[i] != NULL)
	{
		if (options[i][0] == '$' && options[i][1] == '?')
		{
			ft_putstr_fd(ft_itoa(get_minishell()->exit_nb), current->fd_o);
			if (options[i][2] != '\0')
				write(STDOUT_FILENO, &options[i][2], ft_strlen(&options[i][2]));
		}
		else if (options[i][0] == '~' && options[i][1] == '\0')
		{
			builtin_pwd(current, NULL);
			return ;
		}
		else
			write(STDOUT_FILENO, options[i], ft_strlen(options[i]));
		if (options[++i] != NULL)
			write(1, " ", 1);
	}
	if (remove_nl == NO)
		write(STDOUT_FILENO, "\n", 1);
	get_minishell()->exit_nb = SUCCESS;
}

// REVERIFIER LES ECHO $?
// echo $?? , bash print le deuxieme ? comme un char normal.
// echo renvoi 0 on success
// echo renvoi 127 
