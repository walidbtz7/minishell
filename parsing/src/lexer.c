/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/24 20:10:12 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lexer	*init_lexer(char *src)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->src = src;
	lexer->src_lenght = ft_strlen(src);
	lexer->i = 0;
	lexer->quote = 0;
	lexer->c = src[lexer->i];
	return (lexer);
}

void	lexer_advence(t_lexer *lexer)
{
	if (lexer->i < lexer->src_lenght && lexer->c != '\0')
	{
	lexer->i++;
	lexer->c = lexer->src[lexer->i];
	}
}

void	lexer_space_skip(t_lexer *lexer)
{
	while (iswhite(lexer->c))
		lexer_advence(lexer);
}

void	quote_state(t_lexer *lexer)
{
	if ((lexer->c == 34 || lexer->c == 39) && lexer->quote == 0)
		lexer->quote = (int) lexer->c;
	else if ((lexer->c == 34 || lexer->c == 39) && \
	(lexer->quote == (unsigned int) lexer->c))
		lexer->quote = 0;
}

int	stop(t_lexer *lexer)
{
	if (lexer->quote != 34 && lexer->quote != 39)
	{
		if ((istop(lexer->c) || isimposter(lexer->c)))
			return (1);
	}
	else
		if (lexer->c == '\0')
			return (1);
	return (0);
}
