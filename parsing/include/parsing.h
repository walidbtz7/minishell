/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/21 21:46:55 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include "../../global/include/global.h"
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
		HERRDOC
	} e_type;
	char	*file;
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
	t_node	*redirection;
	t_node	*argv;
	t_node	*new;
	char	*str;
	char	**envp;
	int		res;
}	t_parsing;

t_cmd			*init_cmd(t_node *argv, t_node *redirection);
t_redirection	*init_redirection(int type, char *file);
t_argv			*init_argv(char *value);
int				parsing(t_parsing *parse);
void			parsing_analyse(t_parsing *parse);
void			freecmd(t_cmd *cmd);
t_parsing		*init_parse(char **envp);
int				token_red(t_parsing	*parse);
int				token_txt(t_node **argv, t_token *token, char **envp);
int				token_pipe(t_token *token);
#endif