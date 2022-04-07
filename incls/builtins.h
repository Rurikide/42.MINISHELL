#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libsrcs/libft.h"

# define DASH '-'

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
	char	**env;
	int		env_size;
}t_minishell;

t_minishell	*get_minishell(void);
t_answer	ft_is_option(char valid, char *list);
t_answer	ft_is_builtin(char *keyword, char *input);
void		env_var_print(void);
void		env_var_update(char *key, size_t size, char *value);
char		*env_var_get_value(char *key, size_t size);
void		builtin_echo(char **options);
void		builtin_cd(char **options);

#endif
