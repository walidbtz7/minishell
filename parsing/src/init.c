/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/12 04:44:55 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_node	*ft_lstnew(void *content)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		return (NULL);
	n->content = content;
	n->next = NULL;
	return (n);
}

void	ft_nodeadd_back(t_node **node, t_node *new)
{
	t_node	*n;

	n = *node;
	if (!*node)
		*node = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
		new->next = NULL;
	}
}

t_redirection *init_redirection(int type, char	*file)
{
    t_redirection *redirection;

    redirection = malloc(sizeof(t_redirection));
    redirection->type = type;
    redirection->file = file;
    return (redirection);
}

t_argv *init_argv(char	*value)
{
    t_argv *argv;

    argv = malloc(sizeof(t_argv));
    argv->value = value;
    return (argv);
}

t_cmd *init_cmd(t_node *argv, t_node *redirection)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    cmd->argv = argv;
    cmd->redirection = redirection;
    return (cmd);
}

void	printcmd(t_cmd *cmd)
{
    t_node  *argv;
    t_node  *redirection;
	
	argv = cmd->argv;
	redirection = cmd->redirection;
	
	while (argv)
	{
		printf("argv : \t");
		printf("%s \n",((t_argv *)argv->content)->value);
		argv = argv->next;
	}
	while (redirection)
	{
		printf("redirection : \n");			
		printf("%s \n",((t_argv *)argv->content)->value);
		printf("name : %s \n",((t_redirection *)redirection->content)->file);
		printf("type : %d \n",((t_redirection *)redirection->content)->type);
		redirection = redirection->next;
	}
		
}
void	printnode(t_node *head)
{
	t_node	*tmp;
    t_cmd  *cmd;
    t_node  *argv;
    t_node  *redirection;
	int i = 0;
	tmp = head;
	cmd = (t_cmd *) head->content;
	argv =  cmd->argv;
	redirection =  cmd->redirection;
	while (tmp)
	{
		printf("cmd : %i\n",i++);
		while (argv)
		{
			printf("argv : \n");
			printf("%s \n",((t_argv *)argv->content)->value);
			argv = argv->next;
		}
		while (redirection)
		{
			printf("redirection : \n");			
			printf("%s \n",((t_argv *)argv->content)->value);
			printf("name : %s \n",((t_redirection *)redirection->content)->file);
			printf("type : %d \n",((t_redirection *)redirection->content)->type);
			redirection = redirection->next;
		}
		tmp = tmp->next;
 	}
}

void	freecmd(t_cmd *cmd)
{
	t_node 	*tmp;
    t_node  *argv;
    t_node  *redirection;

	argv =  cmd->argv;
	redirection =  cmd->redirection;
	while (argv)
	{
		tmp = argv;
		argv = argv->next;
		free(tmp->content);
		free(tmp);
	}
	while (redirection)
	{
		tmp = redirection;
		redirection = redirection->next;
		free(tmp->content);
		free(tmp);
	}
	free(cmd);

}

void	freeall(t_node **head)
{
	t_node	*tmp;
    t_cmd  *cmd;

	while (*head)
	{
		tmp = (*head);
		cmd = (t_cmd *) (*head)->content;
		freecmd(cmd);
		*head =(*head)->next;
		free(tmp);
	}
}