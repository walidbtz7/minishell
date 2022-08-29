/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/28 23:18:15 by wboutzou         ###   ########.fr       */
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
} t_lexer;

t_lexer *init_lexer(char *src);
void lexer_advence(t_lexer *lexer);
void lexer_space_skip(t_lexer *lexer);
char *lexer_next_token(t_lexer *lexer);
#endif