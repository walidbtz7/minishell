/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/20 17:32:15 by wboutzou         ###   ########.fr       */
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
