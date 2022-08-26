SRCS    		=  ./global/*.c ./parsing/*.c ./execution/*.c main.c

FLAGS 			=	-Wall -Wextra -Werror 

OBJS			=    $(SRCS:.c=.o)


NAME    		=    minishell

.PHONY:		all clean fclean re bonus


all: $(NAME)


$(NAME):  $(HELPERS) $(PRINTF) $(OBJS)
	cc $(FLAGS) $(OBJS) $(PRINTF) $(HELPERS) -o $(NAME)

%.o:%.c 
	cc $(FLAGS) -c $< -o $@

clean:
	@rm -f ${OBJS}

fclean:    clean
	@rm -f ${NAME}

re: fclean all