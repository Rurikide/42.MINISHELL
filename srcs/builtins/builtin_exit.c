/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:13:05 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/18 15:36:19 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


// exit_nb is between 0 and 255.  need to do %256

void    builtin_exit(char **options)
{
    int i;

    i = 0;
    ft_putendl_fd("exit", STDOUT_FILENO);
    if (options[i] != NULL)
    {
        
    }
    // FREE ALL MALLOC , function
    exit(get_minishell()->exit_nb);
}