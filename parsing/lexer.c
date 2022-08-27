/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/27 02:18:32 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lexer.h"

t_lexer *init_lexer(char *src)
{
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    lexer->src = src;
    lexer->i = 0;
    lexer->c = src[lexer->i];

    return (lexer);
}