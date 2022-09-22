/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/20 20:41:51 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;

t_node	*ft_lstnew(void *content);
void	ft_nodeadd_back(t_node **node, t_node *new);
void	printnode(t_node *head);
void	freeall(t_node **head);
int		ft_lstsize(t_node *lst);

#endif