/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/12 13:19:29 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtin_pwd(t_node *current, char **options)
{
	(void)current;
	char	s[PATH_MAX];

	(void)options;
	getcwd(s, sizeof(s));
	ft_putendl_fd(s,  STDOUT_FILENO);
	get_minishell()->exit_nb = SUCCESS;
}
