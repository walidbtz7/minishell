/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/15 11:32:25 by wboutzou         ###   ########.fr       */
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

int    parsing_analyse(t_node    **cmd,t_token *token , char **envp)
{
    int             res;
    t_node         *redirection;
    t_node          *argv;
    t_node          *new;
    
    redirection = NULL;
    res = 1;
    argv = NULL;
    while (token && res == 1)
    {
        if(token_is_red(token->type))
            res = token_red(&redirection, &token);
        else if(token->type == TOKEN_TEXT)
            res = token_txt(&argv, token, envp);
        if((token->type == TOKEN_PIPE || token->next == NULL) && res != 0)
        {
            res = token_pipe(token);
            if(!res)
                return (res);
            new = ft_lstnew(init_cmd(argv, redirection));
            ft_nodeadd_back(cmd, new);
            redirection = NULL;
            argv = NULL;
        }
        token = token->next;
    }
    return (res);
}

