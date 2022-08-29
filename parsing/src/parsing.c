/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/29 01:23:13 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char *lexer_next_token(t_lexer *lexer)
{
    char *token;

    token = NULL;
    while (isalnum(lexer->c))
    {
        token = ft_strjoin(token, &lexer->c);
        lexer_advence(lexer);
    }
    return (token);
}

void parsing(char *src)
{
    t_lexer *lexer = init_lexer(src);
    while (lexer->c != '\0')
    {
        printf("%s\n", lexer_next_token(lexer));
    }
}