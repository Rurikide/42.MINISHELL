/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:16:49 by tshimoda          #+#    #+#             */
/*   Updated: 2022/06/03 17:45:31 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_trim(char *str, char c, int i, int j)
{
	char	*tmp;
	char	*tmp2;
	char	q;

	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			q = str[i];
			tmp[j++] = str[i++];
			while (str[i] != q)
				tmp[j++] = str[i++];
		}
		if (str[i] != c || (str[i - 1] && str[i - 1] != c))
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	tmp2 = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
	ft_strlcpy(tmp2, tmp, ft_strlen(tmp));
	free(str);
	free(tmp);
	return (tmp2);
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
	cu->value = ft_trim(cu->value, ' ', 0, 0);
	if (ft_strlen(cu->value) == 0 || \
		ft_strlen(file) == ft_strlen(cu->value) - ft_count(cu->value, '>'))
		cu->type = 'e';
	*i = -1;
}

	// //
	// printf("file: '%s', len of value: %d, value:'%s\n'", file,
	// ft_strlen(cu->value), cu->value);
void	get_fd_o_open(t_node *cu, char *file, int *fd)
{
	if (*fd != STDOUT_FILENO)
		close(*fd);
	if (cu->type == 'c')
		*fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		*fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	free(file);
}

// int	get_fd_o(t_node *cu, int i, int j, int fd)
// {
// 	int		k;
// 	char	*file;

// 	while (cu->value[++i])
// 	{
// 		if (cu->value[i] == '\'' || cu->value[i] == '"')
// 			ft_iterate(cu, &i, cu->value[i]);
// 		j = 0;
// 		if (cu->value[i] == '>')
// 		{
// 			k = i - 1;
// 			if (cu->value[i + 1] == '>')
// 				cu->type = 'a';
// 			if (cu->value[i + 1] == '>')
// 				i++;
// 			while (cu->value[i] == ' ' || cu->value[i] == '>')
// 				i++;
// 			while (cu->value[i] && cu->value[i] != ' ' && cu->value[i] != '>')
// 				dual_increments(&i, &j);
// 			file = ft_substr(cu->value, i - j, j);
// 			get_fd_o_value(cu, file, &i, k);
// 			get_fd_o_open(cu, file, &fd);
// 			if (cu->type == 'e')
// 				return (fd);
// 		}
// 	}
// 	return (fd);
// }
void	increment_right_redir(t_node *cu, int *i)
{
	if (cu->value[*i + 1] == '>')
	{
		cu->type = 'a';
		*i += 1;
	}
}

int	get_fd_o(t_node *cu, int i, int j, int fd)
{
	int		k;
	char	*file;

	while (cu->value[++i])
	{
		if (cu->value[i] == '\'' || cu->value[i] == '"')
			ft_iterate(cu, &i, cu->value[i]);
		j = 0;
		if (cu->value[i] == '>')
		{
			k = i - 1;
			increment_right_redir(cu, &i);
			while (cu->value[i] == ' ' || cu->value[i] == '>')
				i++;
			while (cu->value[i] && cu->value[i] != ' ' && cu->value[i] != '>')
				dual_increments(&i, &j);
			file = ft_substr(cu->value, i - j, j);
			get_fd_o_value(cu, file, &i, k);
			get_fd_o_open(cu, file, &fd);
			if (cu->type == 'e')
				return (fd);
		}
	}
	return (fd);
}

			// if (cu->value[i + 1] == '>')
			// 	cu->type = 'a';
			// if (cu->value[i + 1] == '>')
			// 	i++;