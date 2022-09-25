/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/25 21:30:35 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_token(t_parsing	*parse)
{
	char	*val;

	val = ft_strldup(parse->token->next->value, \
	ft_strlen(parse->token->next->value));
	parse->error = ft_strjoin(parse->error, val);
	parse->error = ft_strjoin(parse->error, ft_strldup("'", 1));
	while (parse->token->next)
	{
		parse->token = parse->token->next;
	}
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
	char	*tmp;

	if (parse->token->next && parse->token->next->e_type == TOKEN_TEXT)
		token_rm(parse, &new);
	else
	{
		if (parse->token->e_type == TOKEN_HEREDOC)
			parse->herdoc = 0;
		if (!parse->token->next)
			parse->error = ft_strjoin(parse->error, ft_strldup("newline'", 9));
		else
			error_token(parse);
		tmp = ft_strldup(parse->error, ft_strlen(parse->error));
		new = ft_lstnew(init_redirection(ERROR, tmp, 1));
		parse->res = -2;
	}
	ft_nodeadd_back(&(parse->redirection), new);
}

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
