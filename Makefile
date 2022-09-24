NAME    		=    minishell

PARSING    		=   display.c node.c argv_quotes.c argv_expandenv.c argv.c lexer.c \
					tokenization.c init.c analyse.c free.c parsing.c minishell.c

GLOBAL    		=   imposter.c charstr.c strlen.c strchr.c number.c isalnum.c \
					iswhite.c istop.c strldup.c substr.c quotes.c split.c strjoin.c

FLAGS 			=	-Wall -Wextra -Werror -I ./includes

RL_PATH			= -lreadline -L ~/goinfre/homebrew/opt/readline/lib -I ~/goinfre/homebrew/opt/readline/include

OBJS			=    $(SRCS:.c=.o)

SRCS =  $(addprefix global/src/, $(GLOBAL)) \
        $(addprefix parsing/src/, $(PARSING)) \

all: $(NAME)


$(NAME): $(OBJS)
	cc $(FLAGS) $(RL_PATH) $(OBJS) minishell.c -o $(NAME) 

%.o:%.c 
	cc $(FLAGS) -c $< -o $@

clean:
	@rm -f ${OBJS}

fclean:    clean
	@rm -f ${NAME}

re: fclean all

.PHONY:		all clean fclean re bonus
