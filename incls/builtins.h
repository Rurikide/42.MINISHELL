#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef enum s_status
{
	FAIL = -1,
	SUCCESS = 0,
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
}t_minishell;

t_minishell	*get_minishell(void);
t_answer	ft_is_option(char valid, char *list);
t_answer	ft_is_a_match(char *keyword, char *input);
t_answer	is_only_key_identifier(char *option);
void		env_var_print(void);
void		env_var_update(char *key, size_t size, char *update);
int			env_var_get_key_index(char *key, size_t size);
char		*env_var_get_key_value(char *key, size_t size);
char		*env_var_get_value(char *key, size_t size);
void		env_var_add(char *key, size_t size, char *update);
void		env_var_del(char *key, int env_index);
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
int	env_var_matching_key(char *option);
#endif
