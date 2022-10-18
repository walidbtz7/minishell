/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:43:08 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/18 14:29:26 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	norm_direc1(t_redirection *redrec, int *lst_fd)
{
	if (redrec->e_type == OUTPUT)
	{
		if (lst_fd[1] != -1)
		{
			dup2(lst_fd[1], 1);
			close(lst_fd[1]);
		}
		else
			return (0);
	}
	if (redrec->e_type == APPED)
	{
		if (lst_fd[1] != -1)
		{
			dup2(lst_fd[1], 1);
			close(lst_fd[1]);
		}
		else
			return (0);
	}
	return (1);
}

int	norm_direc2(t_redirection *redrec, int *lst_fd, int save)
{
	if (redrec->e_type == INPUT)
	{
		if (lst_fd[0] > 0 && save != -20)
		{
			dup2(lst_fd[0], 0);
			close(lst_fd[0]);
		}
		else if (lst_fd[0] == -20)
			return (0);
	}
	if (redrec->e_type == HERRDOC)
	{
		if (lst_fd[0] != -1 && save != -20)
		{
			write(2, "\n", 1);
			dup2(lst_fd[0], 0);
			close(lst_fd[0]);
		}
		else
			return (0);
	}
	return (1);
}

int	norm_direc3(t_node *my_cmd, int *fd, int *lst_fd, t_redirection *redrec)
{
	if (my_cmd->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (redrec != NULL)
	{
		if (!norm_direc1(redrec, lst_fd))
			return (0);
	}
	return (1);
}

void	norm_direc4(int save, int *fd)
{
	if (save != -20)
		close(fd[0]);
	if (save != -1 && save != -20)
	{
		dup2(save, 0);
		close(save);
	}
}

int	ft_directions(t_node *my_cmd, int *fd, int *lst_fd, int save)
{
	t_redirection	*redrec;
	t_node			*loop;

	redrec = NULL;
	loop = NULL;
	if (((t_cmd *)my_cmd->content)->redirection)
		loop = (((t_cmd *)my_cmd->content)->redirection);
	while (1)
	{
		if (((t_cmd *)my_cmd->content)->redirection)
			redrec = (t_redirection *)loop->content;
		if (!norm_direc3(my_cmd, fd, lst_fd, redrec))
			return (0);
		norm_direc4(save, fd);
		if (redrec != NULL && (!norm_direc2(redrec, lst_fd, save)))
			return (0);
		if (((t_cmd *)my_cmd->content)->redirection)
			loop = loop->next;
		else
			break ;
		if (!loop)
			break ;
	}
	return (1);
}
