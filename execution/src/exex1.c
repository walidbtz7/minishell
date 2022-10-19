/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exex1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:57:29 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 00:36:01 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_for_herrdoc(int *d)
{
	int	res;
	int	status;

	res = 0;
	signal (SIGINT, SIG_IGN);
	while (res != -1)
	{
		res = waitpid(-1, &status, 0);
		if (WIFSIGNALED(status))
			{
				code = 1;
				*d = 1;
			}
		else
			code = 0;
	}
}

void	herrdoc(t_redirection *redrec, char **env, int fd,int *d)
{
	char	*str;
	t_cargv	*dollar;
	int		id;

	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		str = readline("<");
		dollar = NULL;
		while (ft_strcmp(redrec->file, str))
		{
			dollar = init_cargv(str, env);
			if (redrec->expand == 1)
				str = expand_env(dollar);
			ft_putstr_fd(str, fd);
			write(fd, "\n", 1);
			free(str);
			str = readline("<");
		}
		close(fd);
		exit(0);
	}
	wait_for_herrdoc(d);
	close(fd);
}

int	*in_out(t_redirection *red, int *lst_fd)
{
	if (red->e_type == INPUT)
	{
		if (lst_fd > 0)
			close(lst_fd[0]);
		lst_fd[0] = open(red->file, O_RDONLY, 0666);
		if (lst_fd[0] < 0)
		{
			perror(red->file);
			lst_fd[0] = -20;
			code = 1;
		}
	}
	if (red->e_type == OUTPUT)
	{
		if (lst_fd[1] > 0)
			close(lst_fd[1]);
		lst_fd[1] = open(red->file, O_CREAT | O_WRONLY, 0666);
		if (lst_fd[1] < 0)
			perror("red->file");
	}
	return (lst_fd);
}

int	*apped_herr(t_redirection *red, int *lst_fd, char **env,int *d)
{
	int	x;
	int	fd[2];

	x = 0;
	if (red->e_type == APPED)
	{
		if (x != 0)
			close(lst_fd[1]);
		lst_fd[1] = open(red->file, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (lst_fd[1] < 0)
			perror("red->file");
	}
	if (red->e_type == HERRDOC)
	{
		if (x != 0)
			close(lst_fd[0]);
		pipe(fd);
		herrdoc(red, env, fd[1],d);
		lst_fd[0] = fd[0];
		x = 1;
	}
	return (lst_fd);
}
