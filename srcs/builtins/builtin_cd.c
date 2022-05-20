/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:44:44 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/19 22:31:17 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Absolute path starts with '/' meaning at the root
// chdir(char *path) returns 0 on SUCCESS, -1 on FAIL
// if the input is only "cd", chdir will go to the HOME
// BASH BEHAVIOUR if there are more than 1 path
// it will ignore the other arguments
void	builtin_cd_homeless(void)
{
	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	ft_putstr_fd(BUILT_CD, STDERR_FILENO);
	ft_putstr_fd(ERR_HOME, STDERR_FILENO);
	get_minishell()->exit_nb = ERROR_1;
}

void	builtin_cd_error(char *option)
{
	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	ft_putstr_fd(BUILT_CD, STDERR_FILENO);
	ft_putstr_fd(option, STDERR_FILENO);
	ft_putstr_fd(ERR_FILE, STDERR_FILENO);
	get_minishell()->exit_nb = ERROR_1;
}

void	builtin_cd(char **options)
{
	char	s[PATH_MAX];
	char	*home;

	env_var_update("OLDPWD", getcwd(s, sizeof(s)));
	home = env_var_get_value("HOME", 4);
	if (*options == NULL)
	{
		if (home == NULL)
			builtin_cd_homeless();
		else
		{
			chdir(home);
			env_var_update("PWD", home);
		}
	}
	else if (chdir(*options) == FAIL)
		builtin_cd_error(*options);
	else
	{
		env_var_update("PWD", getcwd(s, sizeof(s)));
		get_minishell()->exit_nb = SUCCESS;
	}
}
