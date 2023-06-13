SRCS	=  av.c check.c create.c main.c routine.c timing.c
OBJ		= $(SRCS:.c=.o)
NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all 	: $(NAME)

$(NAME)	: $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re