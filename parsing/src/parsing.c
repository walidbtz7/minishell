/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/10/02 00:35:58 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	token_pipe(t_token *token)
{
	if (token->e_type == TOKEN_PIPE && \
	token->next == NULL)
		return (-1);
	if (token->e_type == TOKEN_PIPE && \
	(token->next->e_type == TOKEN_PIPE))
		return (-1);
	return (1);
}

int	token_is_red(t_parsing *parse)
{
	if (parse->token->next)
	{
		if (parse->token->e_type == TOKEN_HEREDOC && \
		parse->token->next->e_type == TOKEN_TEXT)
			parse->herdoc = 1;
	}
	if (parse->token->e_type == TOKEN_INPUT || \
		parse->token->e_type == TOKEN_OUTPUT || \
		parse->token->e_type == TOKEN_APPEND || \
		parse->token->e_type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

void	parsing_analyse(t_parsing *parse)
{
	while (parse->token && (parse->res == 1 || parse->res == -4))
	{
		if (token_is_red(parse) && parse-> res != -4)
			token_red(parse);
		else if (parse->token->e_type == TOKEN_TEXT && parse-> res != -4)
			token_txt(&(parse->argv), parse->token, parse->envp);
		if ((parse->token->e_type == TOKEN_PIPE || \
parse->token->next == NULL) && parse->res != -1)
		{
			if (parse->res != -2)
				parse->res = token_pipe(parse->token);
			if (parse->res == 0)
				return ;
			if ((parse->argv || parse->redirection) && parse->res != -4)
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
