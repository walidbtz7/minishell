/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/06 19:13:23 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "../../global/include/global.h"

typedef struct token
{
    char *value;
    enum
    {
        TOKEN_INPUT,
        TOKEN_OUTPUT,
        TOKEN_APPEND,
        TOKEN_HEREDOC,
        TOKEN_PIPE,
        TOKEN_TEXT
    } type;
    struct token *next;

} t_token;

t_token *init_token(char *value, int type);
void	ft_tokenadd_back(t_token **token, t_token *new);
void	printtokens(t_token *head);
#endif