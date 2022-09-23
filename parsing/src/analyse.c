/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/23 18:44:58 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	error_token(char	**error, char	*value)
{
	*error = ft_strjoin(*error, value);
	*error = ft_strjoin(*error, "'");
}

void	token_rm(t_parsing	*parse, t_node	**new)
{
	t_cargv	*rm;
	char	*str;
	int		expand;

	expand = 1;
	rm = init_cargv(parse->token->next->value, NULL);
	str = rmquote(rm);
	if (ft_strlen(str) != ft_strlen(parse->token->next->value))
		expand = 0;
	*new = ft_lstnew(init_redirection(parse->token->e_type, \
	str, expand));
	parse->token = parse->token->next;
}

void	token_red(t_parsing	*parse)
{
	t_node	*new;
	char	*error;

	error = ft_strldup("minishell: syntax error near unexpected token `", 48);
	if (parse->token->next && parse->token->next->e_type == TOKEN_TEXT)
	{
		token_rm(parse, &new);
		free(error);
	}
	else
	{
		if (!parse->token->next)
			error = ft_strjoin(error, ft_strldup("newline'", 9));
		else
		{
			error_token(&error, parse->token->next->value);
			parse->token = parse->token->next;
		}
		parse->error = error;
		new = ft_lstnew(init_redirection(ERROR, error, 1));
		parse->res = -2;
	}
	ft_nodeadd_back(&(parse->redirection), new);
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

void	token_txt(t_node **argv, t_token *token, char **envp)
{
	t_cargv	*check;
	t_node	*new;
	char	**str;
	int		i;

	i = 0;
	check = init_cargv(token->value, envp);
	if (!check)
		return ;
	str = fargv(check);
	if (str)
	{
		while (str[i])
		{
			if (str[i])
			{
				check = init_cargv(str[i], envp);
				new = ft_lstnew(init_argv(rmquote(check)));
				ft_nodeadd_back(argv, new);
				free(str[i]);
			}
			i++;
		}
	}
	free(str);
}
