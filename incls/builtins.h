#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
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

typedef	struct s_singleton
{
	int		init;
	char	*login1;
	char	*login2;
}t_singleton;


t_answer	ft_is_option(char valid, char *list);
void		builtin_echo(char **options);
t_answer	ft_is_builtin(char *keyword, char *input);
void		builtin_cd(char **options);

#endif
