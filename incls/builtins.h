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

typedef	struct s_minishell
{
	int		init;
	int		shlvl;
	char	**env;
	int		env_size;
	int		exit_nb;
	int		bu_fd_in;
	int		bu_fd_out;
	int		in_pipeline;
	char	*user_input;
	char	**options;
	t_node *head;
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
void		env_var_print(t_node *current);
void		env_var_print_in_order(t_minishell *ms, t_node *current, int i, int j);
void		env_var_print_quotes(char **table, t_node *current, int equal);
void		env_var_update(char *key, char *update);
void		env_var_add(char *key, char *update);
void		env_var_del(int env_index);
int			env_var_is_key_only(char *option);
int			env_var_matching_key(char *option);
int			env_var_get_key_index(char *key, int size);
char		*env_var_get_key_n_value(char *key);
char		*env_var_get_value(char *key, int size);
int			export_type_key_value(char *option);
void		builtin_echo(t_node *current, char **options);
void		builtin_cd(char **options);
void		builtin_cd_error(char *option);
void		builtin_pwd(t_node *current, char **options);
void		builtin_export(t_node *current, char **options);
void		builtin_unset(t_node *current, char **options);
void		builtin_env(t_node *current, char **options);
void		builtin_exit(t_node *current, char **options);
int			evaluate_export_type(char *option);
void		env_var_export_update(char *update, int pos, int new);
void		ctrl_c_prompt(int signal);
void		ctrl_c_heredoc(int signal);
void		ctrl_d_exit(void);
void		set_signals(void);
void		mute_signals(void);
void		void_signal(int signal);
void		mise_en_abyme(char **options);
void		here_document(t_node *current, char *safeword);
int			execution_builtins(t_node *current, char **options);
void		execution_binary_cmd(t_node *current, int read_fd, char **options);
char		*get_path_value(t_minishell *minishell);
int			execution_access(t_node *current, char **options);
int			search_binary_file(char **path_table, char **options);
void		pipeline_open(t_minishell *minishell);
void		fd_redirection(t_minishell *minishell);
int			is_a_builtin(char **options);
void		pipeline_fork(t_node *current, int read_fd);

#endif
