/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:44:44 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/18 10:58:02 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_answer	ft_is_a_match(char *keyword, char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	if (input == NULL)
		return (NO);
	if (ft_strlen(keyword) != ft_strlen(input))
		return (NO);
	while (i < len)
	{
		if (keyword[i] == input[i])
			i++;
		else
			return (NO);
	}
	return (YES);
}

// Absolute path starts with '/' meaning at the root
// chdir(char *path) returns 0 on SUCCESS, -1 on FAIL
// if the input is only "cd", chdir will go to the HOME
// BASH BEHAVIOUR if there are more than 1 path
// it will ignore the other arguments
void	builtin_cd(char **options)
{
	char	s[PATH_MAX];
	char	*home;

	home = env_var_get_value("HOME=", 5);
	if (home == NULL)
		printf("ERROR? no home variable\n");
	printf("\033[1;33mINITIAL FOLDER is: %s\033[0m\n", getcwd(s, 100));
	if (*options == NULL)
	{
		chdir(home);
	}
	else if (chdir(*options) == FAIL)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(*options, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	env_var_print();
	printf("\033[1;34m------TESTOTOTEST---------\033[0m\n");
	getcwd(s, PATH_MAX);
	env_var_update("OLDPWD", s);
	getcwd(s, PATH_MAX);
	env_var_update("PWD", s);
	env_var_print();
}
