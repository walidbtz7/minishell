/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/21 21:32:50 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	token_red(t_parsing	*parse)
{
	t_node	*new;
	int		i;

	i = 1;
	if (!parse->token->next)
		return (0);
	if (parse->token->next->e_type != TOKEN_TEXT)
		return (0);
	new = ft_lstnew(init_redirection(parse->token->e_type, \
	parse->token->next->value));
	ft_nodeadd_back(&(parse->redirection), new);
	parse->token = parse->token->next;
	return (1);
}

int	token_pipe(t_token *token)
{
	if (token->e_type == TOKEN_PIPE && \
	token->next == NULL)
		return (0);
	if (token->e_type == TOKEN_PIPE && \
	(token->next->e_type == TOKEN_PIPE))
		return (0);
	return (1);
}

int	token_txt(t_node **argv, t_token *token, char **envp)
{
	t_cargv	*check;
	t_cargv	*rm;
	t_node	*new;
	char	**str;

	check = init_cargv(token->value, envp);
	rm = NULL;
	if (!check)
		return (0);
	str = fargv(check);
	if (str)
	{
		while (*str)
		{
			if (*str)
			{
				rm = init_cargv(*str, envp);
				new = ft_lstnew(init_argv(rmquote(rm)));
				ft_nodeadd_back(argv, new);
			}
			str++;
		}
	}
	return (1);
}
