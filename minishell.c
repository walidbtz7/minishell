/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:49:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/07 13:54:47 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    t_cmd   *cmd;

    cmd = NULL;
    while (1)
    {
        parsing(readline("minishell> "), cmd);
    }
    return (0);
}