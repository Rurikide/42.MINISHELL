#include "../incls/builtins.h"
//#include "../libft/libsrcs/libft.h"

void	ft_echo(char *str, int option)
{
	if (option == 0)
	{
		write (1, str, ft_strlen(str));
		write (1, "\n", 1);
	}
	else
		write (1, str, ft_strlen(str));
}
