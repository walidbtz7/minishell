/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/24 17:12:46 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./node.h"
# include "./tokenization.h"
# include "./lexer.h"
# include "./argv.h"

typedef struct argv
{
	char	*value;
}	t_argv;

typedef struct redirection
{
	enum
	{
		INPUT,
		OUTPUT,
		APPED,
		HERRDOC,
		ERROR
	} e_type;
	char	*file;
	int		expand;
}	t_redirection;

typedef struct cmd
{
	t_node	*argv;
	t_node	*redirection;
}	t_cmd;

typedef struct parsing
{
	t_node	*cmd;
	t_lexer	*lexer;
	t_token	*token;
	t_token	*head;
	t_node	*redirection;
	t_node	*argv;
	t_node	*new;
	char	*str;
	char	**envp;
	char	*error;
	int		res;
	int		herdoc;
}	t_parsing;

t_cmd			*init_cmd(t_node *argv, t_node *redirection);
t_redirection	*init_redirection(int type, char *file, int expand);
t_argv			*init_argv(char *value);
int				parsing(t_parsing *parse);
void			parsing_analyse(t_parsing *parse);
void			freecmd(t_cmd *cmd);
void			freeargv(t_node *argv);
void			freeredirection(t_node *redirection);
void			freetoken(t_token **token);
t_parsing		*init_parse(char **envp);
void			token_red(t_parsing	*parse);
void			token_txt(t_node **argv, t_token *token, char **envp);
int				token_pipe(t_token *token);
char			**argvconvert(t_node *argv);
#endif