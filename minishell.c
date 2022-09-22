/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:49:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/22 16:27:35 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_error(t_parsing *parse)
{
	if (parse->herdoc == 0 && parse->res == -2)
	{
		printf("%s\n", parse->error);
		return (0);
	}
	if (parse->res == -1)
	{
		printf("syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_parsing	*parse;

	(void ) argc;
	(void ) argv;
	while (1)
	{
		parse = init_parse(envp);
		parse->str = readline("minishell> ");
		if (parse->str)
			parsing(parse);
		if (parsing_error(parse))
			printnode(parse->cmd);
		freeall(&(parse->cmd));
		free(parse);
	}
	return (0);
}
