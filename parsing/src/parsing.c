/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/11 04:30:09 by wboutzou         ###   ########.fr       */
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
int    parsing_analyse(t_node    **cmd,t_token *token)
{
    t_node          **command;
    int             res;

    res = 0;
    command = cmd;
    while (token)
    {
        parsing_checker(command, token);
        token = token->next;
    }

    return (res);
}

