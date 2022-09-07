/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/07 11:23:37 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "./token.h"

typedef struct lexer
{
    char *src;
    unsigned int src_lenght;
    char c;
    unsigned int i;
    unsigned int quote;
} t_lexer;

t_lexer *init_lexer(char *src);
void lexer_advence(t_lexer *lexer);
void lexer_space_skip(t_lexer *lexer);
int token_type(t_lexer *lexer);
t_token *case_to_handle(t_lexer *lexer);
void quote_state(t_lexer *lexer);
int stop(t_lexer *lexer);
#endif