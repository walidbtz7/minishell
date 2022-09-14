/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/14 02:08:51 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int token_is_red(int    type)
{
    if(type == TOKEN_INPUT || type == TOKEN_OUTPUT || \
        type == TOKEN_APPEND || type == TOKEN_HEREDOC)
        return (1);
    return (0);
}

int    parsing_analyse(t_node    **cmd,t_token *token)
{
    int             res;
    t_node         *redirection;
    t_node          *argv;
    t_node          *new;
    
    redirection = NULL;
    res = 0;
    argv = NULL;
    while (token)
    {
        if(token_is_red(token->type))
            token_red(&redirection, &token);
        else if(token->type == TOKEN_TEXT)
            token_txt(&argv, token);
        if(token->type == TOKEN_PIPE || token->next == NULL)
        {
            new = ft_lstnew(init_cmd(argv, redirection));
            ft_nodeadd_back(cmd, new);
            redirection = NULL;
            argv = NULL;
        }
        token = token->next;
    }
    printnode(*cmd);
    return (res);
}

