/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:04:03 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 00:36:16 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_norm1(t_node *my_cmd, t_ex *ex)
{
	int				*lst_fd;
	int				fd[2];
	int				my_fd;
	int				d=0;
	t_redirection	*redrec;

	my_fd = dup(1);
	if (((t_cmd *)my_cmd->content)->redirection)
		redrec = (t_redirection *)(((t_cmd *)
					my_cmd->content)->redirection->content);
	lst_fd = bull_shit((t_cmd *)my_cmd->content, ex->env,&d);
	if ((((t_cmd *)((my_cmd)->content))->after_expand))
		ft_directions(my_cmd, fd, lst_fd, -20);
	builtins((((t_cmd *)((my_cmd)->content))->after_expand), ex, 0);
	ft_free_e((((t_cmd *)((my_cmd)->content))->after_expand));
	close(lst_fd[1]);
	close(lst_fd[0]);
	dup2(my_fd, 1);
	free(lst_fd);
}

int	ft_close_free(t_node *my_cmd, int *lst_fd, int save, int *fd)
{
	signal (SIGINT, SIG_IGN);
	ft_free_e((((t_cmd *)((my_cmd)->content))->after_expand));
	close(lst_fd[1]);
	close(lst_fd[0]);
	if (save != -1)
		close(save);
	close(fd[1]);
	save = fd[0];
	free(lst_fd);
	return (save);
}

void	ft_sigdftl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	comd(t_node *my_cmd, t_ex *ex)
{
	ft_after_expand(my_cmd);
	run_cmd(ex->env, (((t_cmd *)((my_cmd)->content))->after_expand));
	ft_error((((t_cmd *)((my_cmd)->content))->after_expand));
}
