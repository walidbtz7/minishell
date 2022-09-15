/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/15 12:32:05 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_token *init_token(char *value, int type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    token->value = value;
    token->type = type;
    token->next = NULL;

    return (token);
}


void	ft_tokenadd_back(t_token **token, t_token *new)
{
	t_token	*n;

	n = *token;
	if (!*token)
		*token = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
		new->next = NULL;
	}
}

t_token *case_to_handle(t_lexer *lexer)
{
    if (lexer->c == '>')
    {
        lexer_advence(lexer);
        if(lexer->c == '>')
        {
            lexer_advence(lexer);
            return init_token(">>", TOKEN_APPEND);
        }
        return init_token(">", TOKEN_OUTPUT);
    }
    else if (lexer->c == '<')
    {
        lexer_advence(lexer);
        if(lexer->c == '<')
        {
            lexer_advence(lexer);
            return init_token("<<", TOKEN_HEREDOC);
        }
        return init_token("<", TOKEN_INPUT);
    }
    else if (lexer->c == '|')
    {
        lexer_advence(lexer);
        return init_token("|", TOKEN_PIPE);
    }
    return (0);
}

t_token *lexer_next_token(t_lexer *lexer)
{
    char *value;
    t_token *token;
    char    tmp[2];
    token = NULL;
    value = NULL;
    while (!stop(lexer))
    {
        tmp[0] = lexer->c;
        tmp[1] = '\0';
        value = ft_strjoin(value,tmp);
        quote_state(lexer);
        lexer_advence(lexer);
    }
    if (isimposter(lexer->c) && !value)
        token = case_to_handle(lexer);
    else
        token = init_token(value, TOKEN_TEXT);
    return (token);
}

