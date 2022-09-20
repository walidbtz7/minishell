/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:49:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/20 21:38:55 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_parsing	parse;

	(void ) argc;
	(void ) argv;
	parse = init_parse(envp);
	while (1)
	{
		parse.str = readline("minishell> ");
		if (parse.str)
		{
			if (!parsing(&parse))
			{
				printf("parse error near `|'\n");
				freeall(&(parse.cmd));
			}
			printnode(parse.cmd);
			freeall(&(parse.cmd));
		}
	}
	return (0);
}
