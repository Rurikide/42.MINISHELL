NAME= minishell

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Werrror -Wextra -c

SDIR= srcs
ODIR= objs

SRCS= main.c ft_echo.c

OBJS= $(SRCS:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 

VPATH= $(SDIR)

$(NAME): $(ODIR) $(OFIX)
		$(MAKE) -C ./libft
		$(CC) $(OFIX) -lft -L./libft -Llibread -lreadline -lcurses -I./incls -o $(NAME)

$(ODIR)/%.o: %.c
			$(CC) $(CFLAGS) -I./libft/libsrcs -I./incls $< -o $@

$(ODIR):
		mkdir -p $(ODIR)


all: $(NAME)


clean: 
		$(MAKE) clean -C ./libft
		$(RM) $(ODIR)


fclean: clean
		$(MAKE) fclean -C ./libft
		$(RM) $(NAME)


re: clean all


.PHONY: all clean fclean re