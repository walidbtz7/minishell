/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/15 12:31:03 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int token_red(t_node **redirection, t_token    **token)
{
    t_node  *new;
    int i;
    
    i = 1;
    if(!(*token)->next)
        return (0);
    if((*token)->next->type != TOKEN_TEXT)
        return (0);
    new = ft_lstnew(init_redirection((*token)->type, (*token)->next->value));
    ft_nodeadd_back(redirection, new);
    (*token) = (*token)->next;
    return (1);
}


int token_txt(t_node **argv, t_token    *token , char **envp)
{
    t_node  *new;
    new = ft_lstnew(init_argv(fargv(token->value, envp)));
    ft_nodeadd_back(argv, new);
    return (1);
}

int token_pipe(t_token    *token)
{
    if(token->type == TOKEN_PIPE && token->next == NULL)
        return (0);
    if(token->type == TOKEN_PIPE && (token->next->type == TOKEN_PIPE))
        return (0);
    return (1);
}