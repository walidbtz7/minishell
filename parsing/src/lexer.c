/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/29 02:57:16 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

t_lexer *init_lexer(char *src)
{
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    lexer->src = src;
    lexer->src_lenght = ft_strlen(src);
    lexer->i = 0;
    lexer->c = src[lexer->i];

    return (lexer);
}

void lexer_advence(t_lexer *lexer)
{
    if (lexer->i < lexer->src_lenght && lexer->c != '\0')
    {
        lexer->i++;
        lexer->c = lexer->src[lexer->i];
    }
}

void lexer_space_skip(t_lexer *lexer)
{
    while (iswhite(lexer->c))
        lexer_advence(lexer);
}

int token_type(t_lexer *lexer)
{
    if (lexer->c == '>')
    {
        return (0);
    }
    else if (lexer->c == '<')
    {
        return (1);
    }
    else if (lexer->c == '|')
        return (4);
    else
        return (5);
}
