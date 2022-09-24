SRCS    		=   display.c node.c argv_quotes.c argv_expandenv.c argv.c lexer.c tokenization.c init.c analyse.c free.c parsing.c minishell.c
FLAGS 			=	-Wall -Wextra -Werror 
OBJS			=    $(SRCS:.c=.o)

NAME    		=    parsing.a
RM        		=     rm -f

all:    $(NAME)

$(NAME):
	cd src && cc $(FLAGS) -c $(SRCS)
	cd src && ar rcs ../$(NAME) $(OBJS) 
clean:
	cd src && ${RM} ${OBJS}

fclean:    clean
	${RM} ${NAME}

re:        fclean all

.PHONY:		all clean fclean re bonus