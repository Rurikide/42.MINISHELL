/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:44:44 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/06 16:19:53 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/builtins.h"

t_answer    ft_is_builtin(char *keyword, char *input)
{
	size_t i;
	size_t len;

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

// function searches value of variable in the env
char	*ft_find_env_variable(char *key, size_t size)
{
	t_minishell *ms;

	ms = get_minishell();

	if (ms->env == NULL)
		return (NULL);

	while (ms->env != NULL)
	{
		if (ft_strncmp(*ms->env, key, size) == SUCCESS)
			return (&(*ms->env)[size]);
		else
			ms->env++;
	}
	return (NULL);
}

// Absolute path starts with '/' meaning at the root
// chdir(char *path) returns 0 on SUCCESS, -1 on FAIL
void	builtin_cd(char **options)
{
	char	s[PATH_MAX];
	char	*home;
	
	home = ft_find_env_variable("HOME=", 5);
	if (home == NULL)
		printf("ERROR? no home variable\n");
		
	printf("\033[1;33mINITIAL FOLDER is: %s\033[0m\n", getcwd(s, 100));
	
	// if there input is only "cd", chdir will go to the HOME
	if (*options == NULL)
	{
		chdir(home);
	}
	// BASH BEHAVIOUR if there are more than 1 path, it will ignore the other arguments
	else if (chdir(*options) == FAIL)
	{
		// bash response order
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(*options, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	printf("CURRENT FOLDER is: %s\n", getcwd(s, 100));

	// TO DO UPDATE OLDPWD= && PWD=
}