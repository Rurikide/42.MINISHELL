#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

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

typedef enum e_status
{
	FAIL = -1,
	SUCCESS = 0,
	ERROR_1 = 1,
	ERROR_2 = 2,
	ERROR_127 = 127,
	ERROR_255 = 255,
	SIG_CTR_C = 130,
	SIG_CTR_D = 131
}t_status;

typedef enum e_answer
{
	NO = 0,
	YES = 1,
}t_answer;

typedef struct s_node
{
	char	*value;
	char	type;
	struct  s_node *next;
}t_node; 

typedef	struct s_minishell
{
	int		init;
	int		shlvl;
	char	**env;
	int		env_size;
	int		exit_nb;
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
void		env_var_print(void);
void		env_var_print_in_order(t_minishell *ms, int i, int j);
void		env_var_print_quotes(char **table, int i, int j, int equal);
void		env_var_update(char *key, char *update);
void		env_var_add(char *key, char *update);
void		env_var_del(int env_index);
int			env_var_is_key_only(char *option);
int			env_var_matching_key(char *option);
int			env_var_get_key_index(char *key, int size);
char		*env_var_get_key_n_value(char *key);
char		*env_var_get_value(char *key, int size);
int			export_type_key_value(char *option);
void		builtin_echo(char **options);
void		builtin_cd(char **options);
void		builtin_cd_error(char *option);
void		builtin_pwd(char **options);
void		builtin_export(char **options);
void		builtin_unset(char **options);
void		builtin_env(char **options);
void		builtin_exit(char **options);
int			evaluate_export_type(char *option);
void		env_var_export_update(char *update, int pos, int new);
void		ctrl_c_prompt(int signal);
void		ctrl_d_exit(void);
void		set_signals(void);
void		mute_signals(void);
void		void_signal(int signal);
void		mise_en_abyme(char **options);
void		here_document(char *safeword);
#endif
