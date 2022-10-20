/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:01:55 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 16:39:39 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*bull_shit(t_cmd *cmd, char **env, int *d)
{
	t_redirection	*red;
	t_node			*my_cmd;
	int				*lst_fd;

	my_cmd = NULL;
	lst_fd = (int *)malloc(2 * sizeof (int));
	lst_fd[0] = -1;
	lst_fd[1] = -1;
	my_cmd = cmd->redirection;
	while (my_cmd)
	{
		red = (t_redirection *)my_cmd->content;
		lst_fd = in_out(red, lst_fd);
		lst_fd = apped_herr(red, lst_fd, env, d);
		my_cmd = my_cmd->next;
	}
	return (lst_fd);
}

void	ft_after_expand(t_node *my_cmd)
{
	if (my_cmd)
		((t_cmd *)(my_cmd->content))->after_expand
			= argvconvert(((t_cmd *)my_cmd->content)->argv);
}

void	ft_error(char **str)
{
	if (str)
	{
		if (ft_strchr(str[0], '/'))
		{
			if (!ft_strcmp(str[0], "/"))
			{
				ft_putstr_fd("minishell:  ", 2);
				ft_putstr_fd(str[0], 2);
				ft_putstr_fd(": is a directory\n", 2);
				exit(126);
			}
			else
			{
				ft_putstr_fd("minishell:  ", 2);
				ft_putstr_fd(str[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				exit(127);
			}
		}
		ft_putstr_fd("minishell:  ", 2);
		ft_putstr_fd(str[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

int	ft_nblt(char **str)
{
	if (str)
	{
		if (ft_strcmp(str[0], "echo") && ft_strcmp(str[0], "pwd")
			&& ft_strcmp(str[0], "export") && ft_strcmp(str[0], "unset")
			&& ft_strcmp(str[0], "exit") && ft_strcmp(str[0], "cd")
			&& ft_strcmp(str[0], "env"))
			return (1);
		else
			return (0);
	}
	return (2);
}
