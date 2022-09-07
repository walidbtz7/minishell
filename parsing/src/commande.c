/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/07 14:11:12 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_token *init_cmd(char *value, int type)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    cmd->argv = NULL;
    cmd->redirection = NULL;
    cmd->next = NULL;

    return (cmd);
}


void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*n;

	n = *cmd;
	if (!*cmd)
		*cmd = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
		new->next = NULL;
	}
}


