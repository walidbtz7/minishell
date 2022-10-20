/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:49:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/10/20 18:33:28 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parse(t_parsing *parse)
{
	free(parse->str);
	free(parse->lexer);
	freetoken(&parse->head);
	freeall(&(parse->cmd));
	free(parse->error);
	free(parse);
}

int	parsing_error(t_parsing *parse)
{
	if ((parse->herdoc == 0 && parse->res == -2) || \
	(parse->res == -1) || (parse->res == -3))
	{
		if ((parse->herdoc == 0 && parse->res == -2))
			printf("%s\n", parse->error);
		else if (parse->res == -1)
			printf("syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		code = 1;
	}
}

int	main(int argc, char **argv, char **envp)
{

	t_parsing	*parse;
	t_ex		execu;

	(void ) argc;
	(void ) argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN); 
	code = 0;
	execu.env = ft_dup (envp);
	execu.ex_save = ft_dup(envp);
	while (1)
	{
		parse = init_parse(execu.env);
		parse->str = readline("minishell> ");
		if (parse->str)
		{
			parsing(parse);
			add_history(parse->str);
			if (parsing_error(parse))
				ft_execution(parse->cmd, &execu);
			free_parse(parse);
		}
		else
		{
			return (0);
		}
		
	}
	return (0);
}
