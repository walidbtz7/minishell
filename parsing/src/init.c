/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:56:50 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/22 16:18:00 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_parsing	*init_parse(char **envp)
{
	t_parsing	*parse;

	parse = (t_parsing *) malloc(sizeof(t_parsing));
	parse->argv = NULL;
	parse->cmd = NULL;
	parse->lexer = NULL;
	parse->new = NULL;
	parse->redirection = NULL;
	parse->res = 1;
	parse->str = NULL;
	parse->envp = envp;
	parse->token = NULL;
	parse->herdoc = 0;
	return (parse);
}

t_redirection	*init_redirection(int type, char	*file)
{
	t_redirection	*redirection;

	redirection = (t_redirection *) malloc(sizeof(t_redirection));
	redirection->e_type = type;
	redirection->file = file;
	return (redirection);
}

t_argv	*init_argv(char	*value)
{
	t_argv	*argv;

	argv = (t_argv *) malloc(sizeof(t_argv));
	argv->value = value;
	return (argv);
}

t_cmd	*init_cmd(t_node *argv, t_node *redirection)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) malloc(sizeof(t_cmd));
	cmd->argv = argv;
	cmd->redirection = redirection;
	return (cmd);
}
