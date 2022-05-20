/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:15:52 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/19 22:33:24 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_main(t_node *current, char *file, int fd)
{
	current->eof = ft_strdup(file);
	heredoc_preparation(current);
	dup2(current->fd_i, fd);
	free(current->eof);
}

void	error_open_file(t_node *current, char *file)
{
	current->type = 'e';
	printf("minishell: %s: No such file or directory\n", file);
	free(file);
}

char	*get_fd_i_value(char *value, int *i, int *j, int k)
{
	char	*tmp;

	tmp = ft_strjoin(ft_substr(value, 0, k), (value + *i));
	free(value);
	value = ft_strdup(tmp);
	free(tmp);
	*i = -1;
	*j = 0;
	return (value);
}

void	get_fd_left_redirection(t_node *current, int *i, int *j)
{
	while (current->value[*i] == ' ' || current->value[*i] == '<')
		*i += 1;
	while (current->value[*i] && current->value[*i] != ' ' \
	&& current->value[*i] != '<')
		dual_increments(i, j);
}

int	get_fd_i(t_node *current, int i, int j, int fd)
{
	char	*file;
	int		k;

	while (current->value[i])
	{
		if (current->value[i] == '<')
		{
			k = i;
			get_fd_left_redirection(current, &i, &j);
			file = ft_substr(current->value, i - j, j);
			if (current->value[k] == '<' && current->value[k + 1] == '<')
				heredoc_main(current, file, fd);
			else
			{
				fd = open(file, O_RDONLY);
				if (fd == FAIL)
					error_open_file(current, file);
				if (fd == FAIL)
					break ;
			}
			current->value = get_fd_i_value(current->value, &i, &j, k);
		}
		i++;
	}
	return (fd);
}
