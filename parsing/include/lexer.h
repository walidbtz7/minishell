/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/14 02:05:41 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "./tokenization.h"

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
t_token *lexer_next_token(t_lexer *lexer);
int token_type(t_lexer *lexer);
t_token *case_to_handle(t_lexer *lexer);
t_token *lexer_next_token(t_lexer *lexer);
int      tokenization(t_lexer *lexer, t_token **token);
void    quote_state(t_lexer *lexer);
int     stop(t_lexer *lexer);
#endif