/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/25 18:00:26 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	printargv(t_node *argv)
{
	t_node	*tmp;
	int		i;

	i = 1;
	tmp = argv;
	if (!argv)
		return ;
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
	if (!redirection)
		return ;
	while (tmp)
	{
		printf("\tredirection %d: \n", i++);
		printf("\t\tname : %s \n", ((t_redirection *)tmp->content)->file);
		printf("\t\ttype : %d \n", ((t_redirection *)tmp->content)->e_type);
		if (((t_redirection *)tmp->content)->e_type == HERRDOC)
			printf("\t\texpand : %d \n", ((t_redirection *)tmp->content)->expand);
		tmp = tmp->next;
	}
}

void	printnode(t_node *head)
{
	t_node	*tmp;
	t_cmd	*cmd;
	int		i;

	i = 1;
	tmp = head;
	while (tmp)
	{
		cmd = (t_cmd *) tmp->content;
		printf("cmd %d\n", i++);
		printargv(cmd->argv);
		printredirection(cmd->redirection);
		tmp = tmp->next;
	}
}
