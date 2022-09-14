/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/13 22:20:24 by wboutzou         ###   ########.fr       */
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
	int i = 1;
	int j = 1;
	tmp = head;

	while (tmp)
	{
		cmd = (t_cmd *) tmp->content;
		argv =  cmd->argv;
		redirection =  cmd->redirection;
		printf("cmd : %d\n", i++);
		while (argv)
		{
			printf("\targv : %d\t",j++);
			printf("%s \n",((t_argv *)argv->content)->value);
			argv = argv->next;
		}
		while (redirection)
		{
			printf("redirection : \n");			
			printf("\tname : %s \n",((t_redirection *)redirection->content)->file);
			printf("\ttype : %d \n",((t_redirection *)redirection->content)->type);
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
int	ft_lstsize(t_node *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}