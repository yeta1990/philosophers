SRCS	= srcs/main.c srcs/ft_atoi.c srcs/freezers.c

INCS	= inc/ 

CC		= gcc

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -g

NAME	= philosophers

RM		= rm -f

%.o:%.c
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(INCS)

$(NAME):	$(OBJS) 
			$(CC) $(CFLAGS) $(OBJS) -I$(INCS) -o $(NAME) -lpthread

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

san:		$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -I$(INCS) -o $(NAME) -g0 -O -fsanitize=address 

.PHONY:		all clean fclean re
