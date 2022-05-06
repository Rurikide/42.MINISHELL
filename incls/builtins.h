#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft.h"
# include "parsing.h"

# define TOO_MANY_ARG 1 // bash: exit: too many arguments
# define NON_NUMERIC 255 // bash: exit: var: numeric argument required

typedef enum s_status
{
	FAIL = -1,
	SUCCESS = 0,
	ERROR_1 = 1,
	ERROR_127 = 127  // bash: 0: command not found == 127
}t_status;

typedef enum s_answer
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
	char *user_input;
	char	**options;
	t_node *head;
}t_minishell;

t_minishell	*get_minishell(void);
t_answer	ft_is_option(char valid, char *list);
t_answer	ft_is_a_match(char *keyword, char *input);
t_answer	is_only_key_identifier(char *option);
void		env_var_print(void);
void		env_var_update(char *key, char *update);
void		env_var_add(char *key, char *update);
void		env_var_del(int env_index);
int			env_var_get_key_index(char *key, size_t size);
char		*env_var_get_key_value(char *key);
char		*env_var_get_value(char *key, int size);
void		builtin_echo(char **options);
void		builtin_cd(char **options);
void		builtin_pwd(char **options);
void		builtin_export(char **options);
void		builtin_unset(char **options);
void		builtin_env(char **options);
void		builtin_exit(char **options);
void		init_env(char **env);
int			export_type_key_value(char *option);
void		env_var_print_in_order(t_minishell *ms, int i, int j);
int			env_var_matching_key(char *option);
int			evaluate_export_type(char *option);
void		env_var_export_update(char *update, int i, int new);
void		env_var_export_update(char *update, int pos, int new);
int			env_var_is_key_only(char *option);
void		init_shlvl(void);
#endif
