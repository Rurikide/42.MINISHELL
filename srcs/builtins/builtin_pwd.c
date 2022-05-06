/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/25 12:37:55 by adubeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtin_pwd(char **options)
{
	char	s[PATH_MAX];

	(void)options;
	getcwd(s, PATH_MAX);
	ft_putendl_fd(s, STDIN_FILENO);
	get_minishell()->exit_nb = SUCCESS;
}
