/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:26:50 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/18 13:56:59 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pipe(t_node *my_cmd, t_ex *ex, int save, int *fd)
{
	int		*lst_fd;
	pid_t	id;

	while (my_cmd)
	{
		ft_after_expand(my_cmd);
		lst_fd = bull_shit((t_cmd *)my_cmd->content, ex->env);
		pipe(fd);
		id = fork();
		if (id == 0)
		{
			ft_sigdftl();
			if ((((t_cmd *)((my_cmd)->content))->after_expand))
				if (!ft_directions(my_cmd, fd, lst_fd, save))
					exit(1);
			if (ft_nblt((((t_cmd *)((my_cmd)->content))->after_expand)) == 1)
				comd(my_cmd, ex);
			else
				builtins((((t_cmd *)((my_cmd)->content))->after_expand), ex, 1);
			exit(0);
		}
		save = ft_close_free(my_cmd, lst_fd, save, fd);
		my_cmd = my_cmd->next;
	}
	close(save);
}

void	wait_for_child(void)
{
	int	res;
	int	status;

	res = 0;
	while (res != -1)
	{
		res = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			code = WTERMSIG(status) + 128;
		}
	}
}

void	ft_execution(t_node *cmd, t_ex *ex)
{
	int				fd[2];
	t_node			*my_cmd;
	int				save;
	t_redirection	*redrec;

	my_cmd = cmd;
	save = -1;
	redrec = NULL;
	ft_after_expand(my_cmd);
	if (ft_lstsize(cmd) == 1
		&& !ft_nblt((((t_cmd *)((my_cmd)->content))->after_expand)))
		ft_norm1(my_cmd, ex);
	else
	{
		if (my_cmd)
			ft_free_e((((t_cmd *)((my_cmd)->content))->after_expand));
		ft_pipe(my_cmd, ex, save, fd);
	}
	wait_for_child();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
