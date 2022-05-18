/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:45:45 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/18 16:07:12 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft.h"
# include "parsing.h"

# define ERR_ARGS "too many arguments\n"
# define ERR_CMD "command not found\n"
# define ERR_FILE ": No such file or directory\n"
# define ERR_HOME "HOME not set\n"
# define ERR_KEY "not a valid identifier\n"
# define ERR_NUMERIC "numeric argument required\n"
# define ERR_QUOTES "found unclosed quotes\n"
# define ERR_QUOTES_D "found unclosed double quotes\n"
# define CTRL_D NULL

# define MINISHELL "minishell: "
# define BUILT_CD "cd: "
# define CHILD 0

typedef enum e_status
{
	FAIL = -1,
	SUCCESS = 0,
	ERROR_1 = 1,
	ERROR_2 = 2,
	ERROR_126 = 126,
	ERROR_127 = 127,
	ERROR_255 = 255,
	SIG_CTRL_C = 130,
	SIG_CTRL_D = 131
}t_status;

typedef enum e_answer
{
	NO = 0,
	YES = 1,
}t_answer;

typedef struct s_minishell
{
	int		init;
	int		shlvl;
	char	**env;
	int		env_size;
	int		exit_nb;
	char	*user_input;
	char	**options;
	t_node	*head;
}t_minishell;

t_minishell	*get_minishell(void);
t_answer	ft_is_option(char valid, char *list);
t_answer	ft_is_a_match(char *keyword, char *input);
t_answer	is_only_key_identifier(char *option);
void		init_env(char **env);
void		init_shlvl(void);
void		free_minishell(void);
void		ft_table_del(char **table, int index);
char		**ft_table_add(char **table, const char *new);
void		env_var_print(void);
void		env_var_print_in_order(t_minishell *ms, int i, int j);
void		env_var_print_quotes(char **table, int equal, int i, int j);
void		env_var_update(char *key, char *update);
void		env_var_add(char *key, char *update);
void		env_var_del(int env_index);
int			env_var_is_key_only(char *option);
int			env_var_matching_key(char *option);
int			env_var_get_key_index(char *key, int size);
char		*env_var_get_key_n_value(char *key);
char		*env_var_get_value(char *key, int size);
int			export_type_key_value(char *option);
void		builtin_echo(char **options, int i);
void		builtin_echo_echo(char **options, int i);
void		builtin_echo_empty(void);
void		builtin_echo_exit_nb(char **options, int i);
void		builtin_cd(char **options);
void		builtin_cd_error(char *option);
void		builtin_cd_homeless(void);
void		builtin_pwd(char **options);
void		builtin_export(char **options, int type, int i);
void		builtin_export_invalid_key(char **options, int i);
void		builtin_unset(char **options, int i);
void		builtin_env(char **options);
void		builtin_exit(char **options);
void		builtin_exit_error(char **options, int error_nb);
int			evaluate_export_type(char *option);
void		env_var_export_update(char *update, int pos, int new);
void		ctrl_c_prompt(int signal);
void		ctrl_c_heredoc(int signal);
void		ctrl_d_exit(void);
void		ctrl_d_heredoc_exit(void);
void		set_signals(void);
void		mute_signals(void);
void		void_signal(int signal);
void		heredoc_preparation(t_node *current);
void		heredoc_execution(t_node *current, int *pipe_end);
void		here_document(t_node *current, int *pipe_end, char *safeword);
int			execution_builtins(char **options);
void		execution_main(t_node *current);
int			is_a_builtin(char **options);
void		one_builtin_redirection(t_node *current, char **options);
void		pipeline_fork(t_node *current, int read_fd);
void		pipeline_redirection(t_node *current, int read_fd, int *pipe_end);
void		execution_access(t_minishell *minishell, char **options);
void		search_binary_file(char **path_table, char **options, int i);
char		*get_path_value(t_minishell *minishell);
int			ft_is_matching_strings(char *s1, char *s2);
void		set_exit_nb(int wstatus);
#endif
