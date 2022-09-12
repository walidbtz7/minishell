/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/12 04:52:54 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"


int token_red(t_cmd *cmd, t_token    *token)
{
    t_node  *new;

    if(token->next->type != TOKEN_TEXT)
        return (0);
    new = ft_lstnew(init_redirection(token->type, token->next->value));
    ft_nodeadd_back(&(cmd->redirection), new);
    token = token->next;
    return (1);
}


int token_txt(t_cmd *cmd, t_token    *token)
{
    t_node  *new;
    t_node   *tmp;

    new = ft_lstnew(init_argv(token->value));
    ft_nodeadd_back(&(cmd->argv), new);
    tmp = cmd->argv;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    printf("text : %s\n",((t_argv *)(tmp->content))->value);
    return (1);
}