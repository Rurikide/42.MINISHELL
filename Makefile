NAME= minishell

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Werror -Wextra -g -c

SDIR= srcs
ODIR= objs
BDIR= srcs/builtins
PDIR= srcs/parsing
VDIR= srcs/vector_array

SRCS= main.c

BUILTINS=  builtin_echo.c builtin_cd.c builtin_pwd.c builtin_export.c builtin_unset.c builtin_utils_env.c builtin_utils_env2.c builtin_utils_env3.c builtin_env.c builtin_exit.c
PARSING= parse.c split.c getfd.c nodes.c getvar.c
VECTOR_ARRAY= vector_array.c vector_utils.c

OBJS= $(SRCS:.c=.o) $(BUILTINS:.c=.o) $(PARSING:.c=.o) $(VECTOR_ARRAY:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS))
BFIX= $(addprefix $(BDIR)/, $(BUILTINS))
PFIX= $(addprefix $(PDIR)/, $(PARSING))
VFIX= $(addprefix $(VDIR)/, $(VECTOR_ARRAY)) 

VPATH= $(SDIR) $(BDIR) $(PDIR) $(VDIR)


all: $(NAME)

$(ODIR)/%.o: %.c
			$(CC) $(CFLAGS) -I./libft/libsrcs -I./incls -I./readline $< -o $@

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


.PHONY: all clean fclean re
