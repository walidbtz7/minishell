/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/24 20:10:22 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = value;
	token->e_type = type;
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

t_token	*case_redirection(t_lexer *lexer)
{
	if (lexer->c == '>')
	{
		lexer_advence(lexer);
		if (lexer->c == '>')
		{
			lexer_advence(lexer);
			return (init_token(ft_strldup(">>", 2), TOKEN_APPEND));
		}
		return (init_token(ft_strldup(">", 1), TOKEN_OUTPUT));
	}
	lexer_advence(lexer);
	if (lexer->c == '<')
	{
		lexer_advence(lexer);
		return (init_token(ft_strldup("<<", 2), TOKEN_HEREDOC));
	}
	return (init_token(ft_strldup("<", 1), TOKEN_INPUT));
}

t_token	*case_to_handle(t_lexer *lexer)
{
	if (lexer->c == '>' | lexer->c == '<')
		return (case_redirection(lexer));
	else if (lexer->c == '|')
	{
		lexer_advence(lexer);
		return (init_token(ft_strldup("|", 1), TOKEN_PIPE));
	}
	return (0);
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	char	*value;
	t_token	*token;

	token = NULL;
	value = NULL;
	while (!stop(lexer))
	{
		value = ft_strjoin(value, charstr(lexer->c));
		quote_state(lexer);
		lexer_advence(lexer);
	}
	if (isimposter(lexer->c) && !value)
		token = case_to_handle(lexer);
	else
		token = init_token(value, TOKEN_TEXT);
	return (token);
}
