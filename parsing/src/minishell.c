/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/07 13:54:54 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"


int    parsing(char *src,t_cmd  *cmd)
{
    int res;
    t_lexer *lexer = init_lexer(src);
    t_token *token = NULL;

    if(tokenization(lexer, &token))
    {
        write(2,"Error!\n",7);
        return (1);
    }
    res = parsing_analyse(cmd, token);
    return (res);
}