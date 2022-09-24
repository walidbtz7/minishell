/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:49:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/24 16:38:49 by wboutzou         ###   ########.fr       */
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

void	free_norm(t_parsing *parse)
{
	free(parse->str);
	freetoken(&parse->head);
	freeall(&(parse->cmd));
	free(parse);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_parsing	*parse;

	(void ) argc;
	(void ) argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		parse = init_parse(envp);
		parse->str = readline("minishell> ");
		if (parse->str)
		{
			parsing(parse);
			add_history(parse->str);
			if (parsing_error(parse))
				printnode(parse->cmd);
			free_norm(parse);
		}
		else
			return (0);
	}
	return (0);
}
