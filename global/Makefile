SRCS    		=   imposter.c strlen.c strchr.c number.c isalnum.c  iswhite.c istop.c strldup.c substr.c split.c strjoin.c strjoin_sep.c 

FLAGS 			=	-Wall -Wextra -Werror

OBJS			=    $(SRCS:.c=.o)

NAME    		=    global.a
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