/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:26:50 by mrafik            #+#    #+#             */
/*   Updated: 2022/09/29 20:55:15 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void herrdoc(t_redirection *redrec)
{
	char *str;
	
	str = readline("<");
	while (ft_strcmp(redrec->file,str))
	{
		ft_putstr_fd(str,redrec->fd);
		write(redrec->fd, "\n", 1);
		free(str);
		str = readline("<");
	}
	close(redrec->fd);
}

int	bull_shit(t_cmd *my_cmd)
{
	t_redirection	*red;
	int				fd[2];
	int				x;

	x = 0;
	while (my_cmd->redirection)
	{
		red = (t_redirection *)my_cmd->redirection->content;
		if (red->e_type == INPUT)
		{
			red->fd = open(red->file, O_RDONLY , 0666);
			if (red->fd < 0)
			{
				// perror("red->file");
				// return(1);
			}
		}
		else if (red->e_type == OUTPUT)
		{
			red->fd = open(red->file, O_CREAT | O_WRONLY , 0666);
			if (red->fd < 0)
			{
				// perror("red->file");
				// return(1);
			}
		}
		else if (red->e_type == APPED)
		{
			red->fd = open(red->file, O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (red->fd < 0)
			{
				// perror("red->file");
				// return(1);
			}
		}
		else if (red->e_type == HERRDOC)
		{
			if(x != 0)
				close(fd[0]);
			pipe(fd);
			red->fd = fd[1]; 
			herrdoc(red);
			red->fd = fd[0];
			x = 1;
		}
		my_cmd->redirection = my_cmd->redirection->next;
	}
	return(0);
}


int cd_fuction(char *path_cd)
{
	if(!path_cd)
	{
		free(path_cd);
		path_cd = ft_strdup("/Users");
	}
	if(chdir(path_cd))
		return(printf("faild to %s\n",path_cd));
	return(0);
	
}


void ft_after_expand(t_node *my_cmd)
{
	int i;
	
	i = 0;
	if(my_cmd)
		((t_cmd *)(my_cmd->content))->after_expand = argvconvert(((t_cmd *)my_cmd->content)->argv);
}
void ft_error(char *str)
{
	ft_putstr_fd("minishell>  ",2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n",2);
	exit(0);
}

void ft_pipe(t_node *cmd,char **env)
{
	int fd[2];
	pid_t id;
	t_node *my_cmd;
	int save;
	int i = 0;
	
	t_redirection *redrec;
	
	my_cmd = cmd;
	save = -1;
	redrec = NULL;
	while (my_cmd)
	{
		if(((t_cmd *)my_cmd->content)->redirection)
			redrec = (t_redirection *)(((t_cmd *)my_cmd->content)->redirection->content);
		pipe(fd);
		if (bull_shit((t_cmd *) my_cmd->content))
			return;
		ft_after_expand(my_cmd);
		if(!ft_strcmp((((t_cmd *)((my_cmd)->content))->after_expand)[0],"cd"))
			{
				cd_fuction((((t_cmd *)((my_cmd)->content))->after_expand)[1]);
				break;
			}
		// if(!ft_strcmp((((t_cmd *)((my_cmd)->content))->after_expand)[0],"echo"))
		// 	echo_function((((t_cmd *)((my_cmd)->content))->after_expand));
		id = fork();
		if(id == 0)
		{
			if(my_cmd->next)
			{
				dup2(fd[1], 1);
				close(fd[1]);
			}
			if(redrec != NULL)
			{
				if(redrec->e_type == OUTPUT)
				{
					dup2(redrec->fd, 1);
					close(redrec->fd);
				}
				if(redrec->e_type == APPED)
				{
					dup2(redrec->fd, 1);
					close(redrec->fd);
				}
			}
			if (save != -1)
			{
				dup2(save, 0);
				close(save);
			}
			if(redrec != NULL)
			{
				if(redrec->e_type == HERRDOC)
				{
					dup2(redrec->fd,0);
					close(redrec->fd);
				}
				if(redrec->e_type == INPUT)
				{
					dup2(redrec->fd, 0);
					close(redrec->fd);
				}
			}
			run_cmd(env, (((t_cmd *)((my_cmd)->content))->after_expand));
			ft_error((((t_cmd *)((my_cmd)->content))->after_expand)[0]);
		}
		while ((((t_cmd *)((my_cmd)->content))->after_expand)[i])
		{
			free((((t_cmd *)((my_cmd)->content))->after_expand)[i]);
			i++;
		}
		free((((t_cmd *)((my_cmd)->content))->after_expand));
		if(save != -1)
			close(save);
		close(fd[1]);
		save = fd[0];
		(my_cmd) = (my_cmd)->next;
	}
	int res = 0;
	while(res != -1)
	{
		res = waitpid(-1, NULL, 0);
	}
}
