/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/27 02:02:09 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef struct token
{
    char *value;
    enum
    {
        TOKEN_OUTPUT,
        TOKEN_INPUT,
        TOKEN_TEXT,
        TOKEN_PIPE,
        TOKEN_HEREDOC,
        TOKEN_APPEND
    } type;

} t_token;

t_token *init_token(char *value, int type);
#endif