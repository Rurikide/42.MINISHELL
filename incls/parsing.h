/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:50:49 by adubeau           #+#    #+#             */
/*   Updated: 2022/05/19 22:44:02 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_node
{
	char			*value;
	char			*eof;
	char			type;
	int				fd_i;
	int				fd_o;
	pid_t			id;
	struct s_node	*prev;
	struct s_node	*next;
}t_node;

t_node		*new_node(char *str);
int			ms_parsing(int i);
void		*add_at_end(t_node **head, t_node *new);
int			ms_sanitize(char *input);
void		ms_free_list(t_node *head);
char		**ms_split(char const *s, char sym, unsigned int i, unsigned int len);
int			ft_is_present(char c, char *sym);
int			get_fd_i(t_node *current, int i, int j, int fd);
int			get_fd_o(t_node *cu, int i, int j, int fd);
char		get_type(char *str);
char		*get_var(char *str, int quote, int i);

void		dual_increments(int *i, int *j);
void		heredoc_main(t_node *current, char *file, int fd);
void		error_open_file(t_node *current, char *file);
char		*get_fd_i_value(char *value, int *i, int *j, int k);
void		get_fd_left_redirection(t_node *current, int *i, int *j);
void		get_fd_o_value(t_node *cu, char *file, int *i, int k);
void		get_fd_o_open(t_node *cu, char *file, int *fd);
#endif
