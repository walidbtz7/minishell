/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/14 02:05:29 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "../../global/include/global.h"
#include "./node.h"
#include "./tokenization.h"
#include "./lexer.h"

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


t_cmd       *init_cmd(t_node *argv, t_node *redirection);
t_redirection *init_redirection(int type, char  *file);
t_argv          *init_argv(char *value);
int 	token_red(t_node **redirection, t_token    **token);
int		token_txt(t_node **agrv, t_token    *token);
int      parsing(char *src,t_node  **cmd);
int      parsing_analyse(t_node    **cmd,t_token *token);
void	freecmd(t_cmd *cmd);

#endif