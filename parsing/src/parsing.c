/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/29 03:18:16 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_token *lexer_next_token(t_lexer *lexer)
{
    char *value;
    int type;

    value = NULL;
    type = token_type(lexer);
    while (!iswhite(lexer->c) && lexer->c != '\0')
    {
        type = token_type(lexer);
        value = ft_strjoin(value, &lexer->c);
        lexer_advence(lexer);
    }
    return init_token(value, type);
}

void parsing(char *src)
{
    t_lexer *lexer = init_lexer(src);
    t_token *token;
    while (lexer->c != '\0')
    {
        lexer_space_skip(lexer);
        token = lexer_next_token(lexer);
        lexer_space_skip(lexer);
        printf("token:\n");
        printf("#value : %s \n#type :%d\n", token->value, token->type);
    }
}