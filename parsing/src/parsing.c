/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/07 11:30:42 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_token *lexer_next_token(t_lexer *lexer)
{
    char *value;
    t_token *token;

    token = NULL;
    value = NULL;
    while (!stop(lexer))
    {
        value = ft_strjoin(value, &lexer->c);
        quote_state(lexer);
        lexer_advence(lexer);
    }
    if (isimposter(lexer->c) && !value)
        token = case_to_handle(lexer);
    else
        token = init_token(value, TOKEN_TEXT);
    return (token);
}

int    tokenization(t_lexer *lexer, t_token **token)
{
    while (lexer->c != '\0')
    {
        lexer_space_skip(lexer);
        ft_tokenadd_back(token, lexer_next_token(lexer));
        lexer_space_skip(lexer);
    }
    if(lexer->quote == 1)
        return (1);
    return (0);
}

int    parsing(char *src)
{
    t_lexer *lexer = init_lexer(src);
    t_token *token = NULL;

    if(tokenization(lexer, &token))
    {
        write(2,"Error!\n",7);
        return (1);
    }
    printtokens(token);
    return (0);
}