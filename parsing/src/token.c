/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/06 19:15:45 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/token.h"

t_token *init_token(char *value, int type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    token->value = value;
    token->type = type;
    token->next = NULL;

    return (token);
}


void	ft_tokenadd_back(t_token **token, t_token *new)
{
	t_token	*n;

	n = *token;
	if (!*token)
		*token = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
		new->next = NULL;
	}
}

void	printtokens(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}