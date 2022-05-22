/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:16:49 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/22 11:55:00 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dual_increments(int *i, int *j)
{
	*i += 1;
	*j += 1;
}

void	get_fd_o_value(t_node *cu, char *file, int *i, int k)
{
	char	*sub_str;
	char	*join_str;

	if (ft_is_present('/', file))
	{
		printf("minishell: %s: No such file or directory\n", file);
		get_minishell()->exit_nb = ERROR_1;
	}
	sub_str = ft_substr(cu->value, 0, k);
	join_str = ft_strjoin(sub_str, (cu->value + *i));
	free(cu->value);
	free(sub_str);
	cu->value = join_str;
	*i = -1;
}

void	get_fd_o_open(t_node *cu, char *file, int *fd)
{
	if (cu->type == 'c')
		*fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		*fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	free(file);
}

int	get_fd_o(t_node *cu, int i, int j, int fd)
{
	int		k;
	char	*file;

	while (cu->value[++i])
	{
		j = 0;
		if (cu->value[i] == '>')
		{
			k = i - 1;
			if (cu->value[i + 1] == '>')
				cu->type = 'a';
			if (cu->value[i + 1] == '>')
				i++;
			else
				cu->type = 'c';
			while (cu->value[i] == ' ' || cu->value[i] == '>')
				i++;
			while (cu->value[i] && cu->value[i] != ' ' && cu->value[i] != '>')
				dual_increments(&i, &j);
			file = ft_substr(cu->value, i - j, j);
			get_fd_o_value(cu, file, &i, k);
			get_fd_o_open(cu, file, &fd);
		}
	}
	return (fd);
}
