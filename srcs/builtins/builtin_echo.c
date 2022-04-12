/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:00:31 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/12 12:09:30 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// function scanning the string *list and returns a bool depending on 
// if it only contains the valid option 'n' 
// for the builtin_echo handled in this project.
t_answer	ft_is_option(char valid, char *list)
{
	size_t	i;

	i = 0;
	while (list[i] != '\0')
	{
		if (valid == list[i])
			i++;
		else
			return (NO);
	}
	return (YES);
}

// bash behaviour : can receive multiple -n -n -n -nnnnnnnn options
// which remove the newline. If there is no -n as the first option, 
// it will treat the everything as text input.
// this function receive the array after the echo.
void	builtin_echo(char **options)
{
	t_answer	remove_nl;
	t_answer	is_option;
	int			i;

	i = 0;
	is_option = YES;
	if (options[i] == NULL)
		return ;
	if (*options[i] == '-')
		remove_nl = ft_is_option('n', &(options[i])[1]);
	while (options[i] != NULL && is_option == YES)
	{
		if (*options[i] == '-')
			is_option = ft_is_option('n', &(options[i])[1]);
		if (is_option == YES)
			i++;
	}
	while (options[i] != NULL)
	{
		write(1, options[i], ft_strlen(options[i]));
		if (options[++i] != NULL)
			write(1, " ", 1);
	}
	if (remove_nl == NO)
		write(1, "\n", 1);
}
