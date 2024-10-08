/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/24 20:35:37 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	freetoken(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->value);
		free(tmp);
	}
}

void	freeargv(t_node *argv)
{
	t_node	*tmp;
	t_argv	*targv;

	tmp = argv;
	while (argv)
	{
		tmp = argv;
		argv = argv->next;
		targv = (t_argv *)(tmp->content);
		free(targv->value);
		free(tmp->content);
		free(tmp);
	}
}

void	freeredirection(t_node *redirection)
{
	t_node			*tmp;
	t_redirection	*tred;

	tmp = redirection;
	while (redirection)
	{
		tmp = redirection;
		redirection = redirection->next;
		tred = (t_redirection *)(tmp->content);
		free(tred->file);
		free(tmp->content);
		free(tmp);
	}
}

void	freecmd(t_cmd *cmd)
{
	t_node	*argv;
	t_node	*redirection;

	argv = cmd->argv;
	redirection = cmd->redirection;
	freeargv(argv);
	freeredirection(redirection);
	free(cmd);
}

void	freeall(t_node **head)
{
	t_node	*tmp;
	t_cmd	*cmd;

	while (*head)
	{
		tmp = (*head);
		cmd = (t_cmd *)(*head)->content;
		freecmd(cmd);
		*head = (*head)->next;
		free(tmp);
	}
}
