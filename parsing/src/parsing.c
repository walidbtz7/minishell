/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/21 21:40:36 by wboutzou         ###   ########.fr       */
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

void	parsing_analyse(t_parsing *parse)
{
	while (parse->token && parse->res == 1)
	{
		if (token_is_red(parse->token->e_type))
			parse->res = token_red(parse);
		else if (parse->token->e_type == TOKEN_TEXT)
			parse->res = token_txt(&(parse->argv), parse->token, parse->envp);
		if ((parse->token->e_type == TOKEN_PIPE || \
		parse->token->next == NULL) && parse->res != 0)
		{
			parse->res = token_pipe(parse->token);
			if (!parse->res)
				return ;
			if (parse->argv || parse->redirection)
			{
				parse->new = ft_lstnew(init_cmd(parse->argv, \
				parse->redirection));
				ft_nodeadd_back(&(parse->cmd), parse->new);
				parse->redirection = NULL;
				parse->argv = NULL;
			}
		}
		parse->token = parse->token->next;
	}
}
