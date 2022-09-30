/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:26:50 by mrafik            #+#    #+#             */
/*   Updated: 2022/09/30 22:32:49 by mrafik           ###   ########.fr       */
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

int	*bull_shit(t_cmd *cmd)
{
	t_redirection	*red;
	t_node			*my_cmd = NULL;
	int				fd[2];
	int				x;
	int				*lst_fd;

	lst_fd = (int *)malloc(3 * sizeof (int));
	x = 0;
	
	my_cmd = cmd->redirection;
	while (my_cmd)
	{
		red = (t_redirection *)my_cmd->content;
		if (red->e_type == INPUT)
		{
			if(lst_fd > 0)
				close(lst_fd[0]);
			lst_fd[0] = open(red->file, O_RDONLY , 0666);
			if (lst_fd < 0)
			{ 
				// perror("red->file");
				// return(1);
			}
		}
		else if (red->e_type == OUTPUT)
		{
			if(lst_fd > 0)
				close(lst_fd[1]);
			lst_fd[1] = open(red->file, O_CREAT | O_WRONLY , 0666);
			if (lst_fd < 0)
			{
				// perror("red->file");
				// return(1);
			}
		}
		else if (red->e_type == APPED)
		{
			if(x != 0)
				close(lst_fd[1]);
			lst_fd[1] = open(red->file, O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (lst_fd < 0)
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
			lst_fd[1] = fd[1]; 
			herrdoc(red);
			lst_fd[0] = fd[0];
			x = 1;
		}
		my_cmd = my_cmd->next;
	}
	return(lst_fd);
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
void ft_error(char **str)
{
	if(str)
	{
		ft_putstr_fd("minishell>  ",2);
		ft_putstr_fd(str[0], 2);
		ft_putstr_fd(": command not found\n",2);
		exit(0);
	}
}

void ft_pipe(t_node *cmd,char **env)
{
	int fd[2];
	pid_t id;
	t_node *my_cmd;
	int save;
	int	*lst_fd;
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
		ft_after_expand(my_cmd);
		lst_fd = bull_shit((t_cmd *)my_cmd->content);
		id = fork();
		if(id == 0)
		{
			if((((t_cmd *)((my_cmd)->content))->after_expand))
			{
				ft_directions(my_cmd,fd,lst_fd,save);
				if(!ft_strcmp((((t_cmd *)((my_cmd)->content))->after_expand)[0],"cd"))
					cd_fuction((((t_cmd *)((my_cmd)->content))->after_expand)[1]);
				if(!ft_strcmp((((t_cmd *)((my_cmd)->content))->after_expand)[0],"echo"))
					echo_function((((t_cmd *)((my_cmd)->content))->after_expand));
			}
			run_cmd(env, (((t_cmd *)((my_cmd)->content))->after_expand));
			ft_error((((t_cmd *)((my_cmd)->content))->after_expand));
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
