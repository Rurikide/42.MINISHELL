NAME= minishell

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Werror -Wextra -ggdb3 -c

SDIR= srcs
ODIR= objs
BDIR= srcs/builtins
PDIR= srcs/parsing
EDIR= srcs/execution

SRCS= main.c

BUILTINS=  builtin_echo.c builtin_cd.c builtin_pwd.c builtin_export.c builtin_unset.c builtin_utils_env.c builtin_utils_env2.c builtin_utils_env3.c builtin_env.c builtin_exit.c builtins_list.c environment.c
EXECUTION= access.c execution.c heredoc.c minishell_utils.c signal.c toggle_signal.c
PARSING= parse.c split.c get_fd_i.c get_fd_o.c nodes.c getvar.c sanitize.c
OBJS= $(SRCS:.c=.o) $(BUILTINS:.c=.o) $(EXECUTION:.c=.o) $(PARSING:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS))
BFIX= $(addprefix $(BDIR)/, $(BUILTINS)) 
EFIX= $(addprefix $(EDIR)/, $(EXECUTION)) 
PFIX= $(addprefix $(PDIR)/, $(PARSING)) 

VPATH= $(SDIR) $(BDIR) $(EDIR) $(PDIR)


all: $(NAME)

$(ODIR)/%.o: %.c
			$(CC) $(CFLAGS) -I./libft/libsrcs -I./incls -I. $< -o $@

$(ODIR):
		mkdir -p $(ODIR)

$(NAME): $(ODIR) $(OFIX)
		$(MAKE) -C ./libft
		$(CC) $(OFIX) -lft -L./libft -Llibread -lreadline -lcurses -o $(NAME)

clean: 
		$(MAKE) clean -C ./libft
		$(RM) $(ODIR)


fclean: clean
		$(MAKE) fclean -C ./libft
		$(RM) $(NAME)


re: clean all


val: all
	valgrind --leak-check=full --track-origins=yes --trace-children=yes ./minishell

.PHONY: all clean fclean re val

#--show-leak-kinds=all --verbose