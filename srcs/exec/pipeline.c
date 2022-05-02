/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:03:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/02 10:39:58 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    pipeline_connections(void)
{
    /*
        t_minishell *minishell;
        t_node  starting_point;

        minishell = get_minishell();

        starting_point = minishell->node->cmd;
        while (minishell->node->cmd != NULL ???)
        {
            dup2(minishell->node->in_fd, STDIN_FILENO);
            close(minishell->node->in_fd);
            minishell->node->cmd = minishell->node->cmd->next;
        }
        minishell->node->cmd = starting_point;
    */    
}

void pipeline_shut_down(void)
{
    /*
        t_minishell *minishell;
        t_node starting_point;

        minishell = get_minishell();
        starting_point = minishell->node->cmd;
        while (minishell->node->cmd != NULL)
        {
            close(minishell->node->in_fd);
            close(minishell->node->out_fd);
        }
        minishell->node->cmd = starting_point;
    */
}