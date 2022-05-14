/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/14 13:37:45 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtin_pwd(char **options)
{
	char	s[PATH_MAX];

	(void)options;
	getcwd(s, sizeof(s));
	ft_putendl_fd(s,  STDOUT_FILENO);
	get_minishell()->exit_nb = SUCCESS;
}
