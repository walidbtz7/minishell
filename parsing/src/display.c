/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/20 20:39:13 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	printargv(t_node *argv)
{
	t_node	*tmp;
	int		i;

	i = 1;
	tmp = argv;
	while (tmp)
	{
		printf("\targv %d:\n", i++);
		printf("\t\t%s \n", ((t_argv *) tmp->content)->value);
		tmp = tmp->next;
	}
}

void	printredirection(t_node *redirection)
{
	t_node	*tmp;
	int		i;

	i = 1;
	tmp = redirection;
	while (tmp)
	{
		printf("\tredirection %d: \n", i++);
		printf("\t\tname : %s \n", ((t_redirection *)tmp->content)->file);
		printf("\t\ttype : %d \n", ((t_redirection *)tmp->content)->e_type);
		tmp = tmp->next;
	}
}

void	printnode(t_node *head)
{
	t_node	*tmp;
	t_cmd	*cmd;

	tmp = head;
	while (tmp)
	{
		cmd = (t_cmd *) tmp->content;
		printargv(cmd->argv);
		printredirection(cmd->redirection);
		tmp = tmp->next;
	}
}
