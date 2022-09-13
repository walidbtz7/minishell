SRCS    		=   minishell.c

FLAGS 			=	-Wall -Wextra -Werror -g -fsanitize=address 

OBJS			=    $(SRCS:.c=.o)

NAME    		=    minishell

GLOBAL    		=    ./global/global.a

PARSING    		=    ./parsing/parsing.a

EXECUTION  		=    ./ft_printf/execution.a

.PHONY:		all clean fclean re bonus


all: $(NAME)


$(NAME):  $(GLOBAL) $(PARSING) $(OBJS)
	cc $(FLAGS) $(GLOBAL) $(PARSING) $(OBJS) -o $(NAME) -lreadline 

$(GLOBAL):
	@make -C global

$(PARSING):
	@make -C parsing

$(EXECUTION):
	@make -C execution

%.o:%.c 
	cc $(FLAGS) -c $< -o $@

clean:
	@rm -f ${OBJS}
	@make  -C global clean
	@make  -C parsing clean

fclean:    clean
	@make  -C global fclean
	@make  -C parsing fclean
	@rm -f ${NAME}

re: fclean all