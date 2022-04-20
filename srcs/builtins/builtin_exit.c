/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:13:05 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/20 15:07:57 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


// exit_nb is between 0 and 255.  need to do %256

void    builtin_exit(char **options)
{
    t_minishell *minishell;
    
    minishell = get_minishell();
    int i;

    i = 0;
    ft_putendl_fd("exit", STDOUT_FILENO);
    // if (options[i] != NULL)
    // {
        
    // }
    
   ft_free_table(minishell->env);
   ft_free_table(minishell->options);
   free(minishell->user_input);
   // rl_clear_history();
    exit(get_minishell()->exit_nb);
}
