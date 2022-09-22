/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/21 19:16:52 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	tokenization(t_lexer *lexer, t_token **token)
{
	while (lexer->c != '\0')
	{
		lexer_space_skip(lexer);
		ft_tokenadd_back(token, lexer_next_token(lexer));
		lexer_space_skip(lexer);
	}
	if (lexer->quote == 34 || lexer->quote == 39)
		return (1);
	return (0);
}

int	tokenization_checker(t_token	*token)
{
	if (!token || !token->value)
		return (0);
	if (token->e_type == TOKEN_PIPE)
		return (-1);
	return (1);
}

int	parsing(t_parsing *parse)
{
	parse->res = 1;
	parse->token = NULL;
	parse->lexer = init_lexer(parse->str);
	if (tokenization(parse->lexer, &(parse->token)))
	{
		write(2, "Error!\n", 7);
		return (1);
	}
	parse->res = tokenization_checker(parse->token);
	parsing_analyse(parse);
	return (parse->res);
}
