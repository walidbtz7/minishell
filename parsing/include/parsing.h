/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/07 14:11:18 by wboutzou         ###   ########.fr       */
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

typedef struct argv
{
  enum
    {
       commande,
       option,
    } type;
   char *argv;
} t_argv;

typedef struct redirection
{
    enum
    {
       INPUT,
       OUTPUT,
    } type;
   char *file;
} t_redirection;

typedef struct cmd
{
   t_argv *argv;
   t_argv *redirection;
   struct cmd    *next;
} t_cmd;

t_token *lexer_next_token(t_lexer *lexer);
int      parsing(char *src,t_cmd  *cmd);
int      tokenization(t_lexer *lexer, t_token **token);
int      parsing_analyse(t_cmd    *cmd,t_token *token);
t_token *init_cmd(char *value, int type);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
#endif