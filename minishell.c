/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:49:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/14 02:10:08 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    t_node   *cmd;

    cmd = NULL;
    while (1)
    {
        parsing(readline("minishell> "), &cmd);
        freeall(&cmd);
    }
    return (0);
}