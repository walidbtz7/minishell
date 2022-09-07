/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/07 14:04:13 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int parsing_checker(t_cmd *cmd, t_token *token)
{
    int res;

    if(token->type == TOKEN_INPUT || token->type == TOKEN_OUTPUT)
        res = token_red(cmd, token);
    else if(token->type == TOKEN_APPEND)
        res = token_app(cmd, token);
    else if(token->type == TOKEN_HEREDOC)
        res = token_hdc(cmd, token);
    else if(token->type == TOKEN_PIPE)
        res = token_pipe(cmd, token);
    else
        res = token_txt(cmd, token);
    return (res);
}

int token_red(t_cmd *cmd, t_token    *token)
{
    if(token->next->type != TOKEN_TEXT)
        return (0);
    return (1);
}

int token_app(t_cmd *cmd, t_token    *token)
{
    if(token->next->type != TOKEN_TEXT)
        return (0);
    return (1);
}

int token_hdc(t_cmd *cmd, t_token    *token)
{
    if(token->next->type != TOKEN_TEXT)
        return (0);
    return (1);
}

int token_pipe(t_cmd *cmd, t_token    *token)
{
    if(token->next->type == TOKEN_PIPE || token->next == NULL)
        return (0);
    return (1);
}

int token_txt(t_cmd *cmd, t_token    *token)
{
    return (1);
}