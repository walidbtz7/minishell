/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/15 11:47:38 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"


int tokenization(t_lexer *lexer, t_token **token)
{
    while (lexer->c != '\0')
    {
        lexer_space_skip(lexer);
        ft_tokenadd_back(token, lexer_next_token(lexer));
        lexer_space_skip(lexer);
    }
    if(lexer->quote == 34 || lexer->quote == 39)
        return (1);
    return (0);
}

int    parsing(char *src,t_node  **cmd, char **envp)
{
    int res;
    t_lexer *lexer = init_lexer(src);
    t_token *token = NULL;

    if(tokenization(lexer, &token))
    {
        write(2,"Error!\n",7);
        return (1);
    }
    res = parsing_analyse(cmd, token, envp);
    return (res);
}