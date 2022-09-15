/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:49:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/15 11:44:51 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char** envp)
{
    t_node   *cmd;
    char    *str;

    (void ) argc;
    (void ) argv;
    cmd = NULL;
    while (1)
    {
        str = readline("minishell> ");
        if(str)
        {
            if(!parsing(str, &cmd, envp))
                printf("Syntax Error!\n");
            printnode(cmd);
            freeall(&cmd);
        }
    }
    return (0);
}