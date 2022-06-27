NAME	=	philo_bonus

SRCS	=	ft_atoi.c \
			init_bonus.c \
			main_bonus.c \
			philo_bonus.c \
			time_bonus.c \
			utils_bonus.c \

HEADER	=	philo_bonus.h

OBJ		=	$(patsubst %.c, %.o, $(SRCS))

# CDEBUG	=	-fsanitize=address

CC		=	cc -pthread

CFLAGS	=	-Wall -Wextra -Werror

.PHONY	:	all clean fclean re

all 	:	$(NAME)

$(NAME)	: 	$(OBJ) $(HEADER)
			$(CC) $(CFLAGS) $(CDEBUG) $(OBJ) -o $(NAME)

%.o	: %.c	$(HEADER)
			$(CC) $(CFLAGS) $(CDEBUG) -c $< -o $@

clean	:
	@rm -rf $(OBJ)

fclean	:	clean
	@rm -f $(NAME)

re		:	fclean all
