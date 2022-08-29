/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/29 06:35:05 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_token *lexer_next_token(t_lexer *lexer)
{
    char *value;
    int type;
    t_token *token;

    token = NULL;
    value = NULL;
    type = token_type(lexer);
    while (!istop(lexer->c) && !case_to_handle(lexer))
    {
        type = token_type(lexer);
        value = ft_strjoin(value, &lexer->c);
        lexer_advence(lexer);
        printf("%c", lexer->c);
    }
    if (value != NULL)
        token = init_token(value, type);
    free(value);
    return (token);
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