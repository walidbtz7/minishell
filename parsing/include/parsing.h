/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/12 04:38:37 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H
  
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "./lexer.h"

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;

typedef struct argv
{
   char  *value;
}	t_argv;

typedef struct redirection
{
	enum
	{
	  INPUT,
	  OUTPUT,
	  APPED,
	  HERRDOC
	} type;
   char *file;
} t_redirection;

typedef struct cmd
{
   t_node *argv;
   t_node *redirection;
} t_cmd;

// node
t_node	*ft_lstnew(void *content);
void     ft_nodeadd_back(t_node **node, t_node *new);
void	printnode(t_node *head);
void	printcmd(t_cmd *cmd);
void	freeall(t_node **head);
void	freecmd(t_cmd *cmd);
// init
t_cmd       *init_cmd(t_node *argv, t_node *redirection);
t_redirection *init_redirection(int type, char  *file);
t_argv          *init_argv(char *value);

// token check
int 	token_red(t_cmd *cmd, t_token    *token);
int		token_txt(t_cmd *cmd, t_token    *token);
// scanner
int      parsing(char *src,t_node  **cmd);
int      parsing_analyse(t_node    **cmd,t_token *token);
int      parsing_checker(t_node **cmd, t_token *token);

#endif