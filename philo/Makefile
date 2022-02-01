SRCS	= srcs/main.c srcs/ft_atoi.c srcs/freezers.c \
		  srcs/time_utils.c srcs/mutex_and_threads.c \
		  srcs/routines.c srcs/create_philos.c

INCS	= inc/ 

CC		= gcc

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

NAME	= philo

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

.PHONY:		all clean fclean re
