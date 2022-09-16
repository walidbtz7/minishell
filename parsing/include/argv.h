/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/16 09:03:02 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H
#define ARGV_H

typedef struct cargv
{
    char *src;
    char c;
    int i;
    char    **envp;
    int start;
    int single;
    int expand;
    int dbl;
} t_cargv;

t_cargv *init_cargv(char *src, char **envp);

#endif