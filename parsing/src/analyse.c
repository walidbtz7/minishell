/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/11 04:43:13 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int parsing_checker(t_node **cmd, t_token *token)
{
    int res;

    res = 1;
    if(token->type == TOKEN_INPUT || token->type == TOKEN_OUTPUT || \
    token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
        token_red(cmd, token);
    else if(token->type == TOKEN_PIPE)
        token_pipe(cmd, token);
    if(token->type == TOKEN_TEXT)
        token_txt(cmd, token);
    token = token->next;
    return (res);
}

int token_red(t_node **cmd, t_token    *token)
{
    t_cmd  *head;
    t_node  *new;
    head = (t_cmd *) ((*cmd)->content);
    if(token->next->type != TOKEN_TEXT)
        return (0);
    new = ft_lstnew(init_redirection(token->type, token->next->value));
    ft_nodeadd_back(&(head->redirection), new);
    token = token->next;
    return (1);
}

int token_pipe(t_node **cmd, t_token    *token)
{
    t_node  *new;
    if(token->next->type == TOKEN_PIPE || token->next == NULL)
        return (0);
    new = ft_lstnew(init_cmd());
    ft_nodeadd_back(cmd, new);
    return (1);
}

int token_txt(t_node **cmd, t_token    *token)
{
    t_cmd  *head;
    t_node  *new;
    head = (t_cmd *) ((*cmd)->content);
    new = ft_lstnew(init_argv(token->value));
    ft_nodeadd_back(&(head->argv), new);
    token = token->next;
    return (1);
}