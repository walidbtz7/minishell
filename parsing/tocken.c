/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/08/27 02:10:05 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/token.h"

t_token *init_token(char *value, int type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    token->value = value;
    token->type = type;

    return (token);
}
