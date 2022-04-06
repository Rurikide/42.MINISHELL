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
}t_minishell;

t_minishell	*get_minishell(void);
char	*ft_find_env_variable(char *key, size_t size);
t_answer	ft_is_option(char valid, char *list);
void		builtin_echo(char **options);
t_answer	ft_is_builtin(char *keyword, char *input);
void		builtin_cd(char **options);

#endif
