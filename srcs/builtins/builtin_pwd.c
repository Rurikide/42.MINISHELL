/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/15 12:06:49 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtin_pwd(char **options)
{
	char	s[PATH_MAX];

	printf("options = %s\n", options[0]);
	getcwd(s, PATH_MAX);
	ft_putendl_fd(s, STDIN_FILENO);
}

	// if (&options[0] == '-')
	// {
	//         if (ft_is_a_match("-LP", options[0]) == YES)
	// maybe not necessary to handle the flags
	// }