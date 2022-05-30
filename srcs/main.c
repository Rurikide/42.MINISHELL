/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:10:03 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/27 12:26:35 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_str_spacetab(char *str)
{
	int len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	minishell_loop(t_minishell *minishell)
{
	t_node	*current;

	if (minishell->user_input != NULL)
		free(minishell->user_input);
	minishell->user_input = readline("minishell> ");
	if (minishell->user_input == CTRL_D)
		ctrl_d_exit();
	if (ft_is_str_spacetab(minishell->user_input) == SUCCESS)
	{
		ms_free_list(minishell->head);
		minishell->head = NULL;
	}
	else if (minishell->user_input[0] != '\0')
	{
		add_history(minishell->user_input);
		if (ms_parsing(minishell, 1) == 1)
		{
			current = minishell->head;
			execution_main(current);
		}
		ms_free_list(minishell->head);
		minishell->head = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	if (argc > 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		minishell = get_minishell();
		minishell->exit_nb = ERROR_127;
		free_minishell();
		return (minishell->exit_nb);
	}
	init_env(env);
	minishell = get_minishell();
	set_signals();
	while (true)
	{
		minishell_loop(minishell);
	}
	free_minishell();
	return (minishell->exit_nb);
}
