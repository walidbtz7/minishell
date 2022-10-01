/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/10/01 06:44:50 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_token(t_parsing	*parse)
{
	char	*val;

	val = ft_strldup(parse->token->next->value, \
	ft_strlen(parse->token->next->value));
	parse->error = ft_strjoin_free(parse->error, val);
	parse->error = ft_strjoin_free(parse->error, ft_strldup("'", 1));
	while (parse->token->next)
	{
		parse->token = parse->token->next;
	}
}

int	ambiguous_red(char	*str)
{
	if (!str[0])
	{
		printf("ambiguous redirect\n");
		free(str);
		return (0);
	}
	return (1);
}

char	*fred(t_cargv *check)
{
	char	*new;
	char	*expend;

	new = ft_strldup("", 0);
	expend = NULL;
	while (check->c)
	{
		double_quote(check);
		single_quote(check);
		if (check->c == '$')
			new = ft_strjoin_free(new, expandenv(check));
		else
		{
			new = ft_strjoin_free(new, charstr(check->c));
			cargv_advence(check);
		}
	}
	free(check);
	return (new);
}

void	token_rm(t_parsing	*parse, t_node	**new)
{
	t_cargv	*check;
	char	*str;
	int		expand;
	char	*tmp;

	expand = 1;
	check = NULL;
	str = parse->token->next->value;
	if (parse->token->e_type != TOKEN_HEREDOC)
	{
		check = init_cargv(str, parse->envp);
		str = fred(check);
		tmp = str;
	}
	else
		tmp = ft_strldup("", 0);
	check = init_cargv(str, NULL);
	str = rmquote(check);
	free(tmp);
	if (ft_strlen(str) != ft_strlen(parse->token->next->value))
		expand = 0;
	if (ambiguous_red(str))
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
		if (!parse->token->next)
		parse->error = ft_strjoin_free(parse->error, ft_strldup("newline'", 9));
		else
			error_token(parse);
		tmp = ft_strldup(parse->error, ft_strlen(parse->error));
		new = ft_lstnew(init_redirection(ERROR, tmp, 1));
		parse->res = -2;
	}
	if (new->content)
		ft_nodeadd_back(&(parse->redirection), new);
}
