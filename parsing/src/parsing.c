/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/20 21:56:57 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	token_is_red(int type)
{
	if (type == TOKEN_INPUT || type == TOKEN_OUTPUT || \
		type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	parsing_analyse(t_parsing *parse)
{
	t_token	*token;

	token = parse->token;
	if (token->e_type == TOKEN_PIPE)
		return (0);
	while (token && parse->res == 1)
	{
		if (token_is_red(token->e_type))
			token_red(parse);
		else if (token->e_type == TOKEN_PIPE || token->next == NULL)
		{
			parse->res = token_pipe(token);
			if (!parse->res)
				return (parse->res);
			if (parse->argv || parse->redirection)
			{
				parse->new = ft_lstnew(init_cmd(parse->argv, \
				parse->redirection));
				ft_nodeadd_back(parse->cmd, parse->new);
				parse->redirection = NULL;
				parse->argv = NULL;
			}
		}
		token = token->next;
	}
}
