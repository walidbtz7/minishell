/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/12 04:38:09 by wboutzou         ###   ########.fr       */
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
    int             res;
    t_node         *new;
    t_cmd           *commande;

    res = 1;
    
    commande = init_cmd(NULL, NULL);
    while (token)
    {
        if(token->type == TOKEN_INPUT || token->type == TOKEN_OUTPUT || \
        token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
            token_red(commande, token);
        else if(token->type == TOKEN_TEXT)
            token_txt(commande, token);
        if(token->type == TOKEN_PIPE || token->next == NULL)
        {
            new = ft_lstnew(init_cmd(commande->argv, commande->redirection));
            ft_nodeadd_back(cmd, new);
            commande = init_cmd(NULL , NULL);
        }
        token = token->next;
    }
    printnode(*cmd);
    return (res);
}
