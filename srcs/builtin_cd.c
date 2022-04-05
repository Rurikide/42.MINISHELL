/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:44:44 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/05 16:54:16 by tshimoda         ###   ########.fr       */
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


// Absolute path starts with '/' meaning at the root

void	builtin_cd(char **options)
{
    if (*options == NULL)
        printf("\033[1;34mis empty\n\033[0m");

    char s[100];
  
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
  
    // using the command
    chdir("..");
  
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
}