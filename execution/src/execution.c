/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:26:50 by mrafik            #+#    #+#             */
/*   Updated: 2022/09/27 21:16:33 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bull_shit(t_cmd *my_cmd)
{
	t_redirection	*red;

	while (my_cmd->redirection)
	{
		red = (t_redirection *)my_cmd->redirection->content;
		if (red->e_type == INPUT)
		{
			red->fd = open(red->file, O_RDONLY , 0666);
			if (red->fd < 0)
			{
				perror("red->file");
				return(1);
			}
		}
		else if (red->e_type == OUTPUT)
		{
			red->fd = open(red->file, O_CREAT | O_WRONLY , 0666);
			if (red->fd < 0)
			{
				perror("red->file");
				return(1);
			}
		}
		else if (red->e_type == APPED)
		{
			red->fd = open(red->file, O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (red->fd < 0)
			{
				perror("red->file");
				return(1);
			}
		}
		my_cmd->redirection = my_cmd->redirection->next;
	}
	return(0);
}

char	*avai_path(char *str,char *cmd)
{
	char	**pos;
	int		i;

	i = 0;
	pos = ft_split(ft_split(str, '=')[1], ':');
	while(pos[i])
	{
		if (open(ft_strjoin(pos[i],cmd),0)  != -1)
		{
			return (ft_strjoin(pos[i],cmd));
		}
		i++;
	}
	return (NULL);
}

void run_cmd(char **env,char **av)
{
	char *cmd_path;
	char *cmd;

	cmd = ft_strjoin("/", av[0]);
	cmd_path = avai_path(path(env, "PATH"), cmd);
	execve(cmd_path,av, env);
}
int cd_fuction(char *path)
{
	if(chdir(path))
		return(printf("faild to %s\n",path));
	return(0);
	
}
char *path(char **env,char *search)
{
	int i;
	int j;
	
	i = 0;
	while(env[i])
	{
		j = 0;
		while(env[i][j])
		{
			if(env[i][j] == search[j] && (env[i][j] != '\0' || search[j] != '\0'))
			{
				j++;
				if(!search[j])
					return (env[i]);
			}
			else
				break;
		}
		i++;
	}
	return(NULL);
}

void ft_after_expand(t_node *my_cmd)
{
	int i;
	
	i = 0;
	if(my_cmd)
		((t_cmd *)(my_cmd->content))->after_expand = argvconvert(((t_cmd *)my_cmd->content)->argv);
	
}
 
void ft_pipe(t_node *my_cmd,char **env)
{
	int fd[2];
	pid_t id;
	int save;
	t_redirection *redrec;
	
	save = -1;
	while (my_cmd)
	{
		if((t_redirection *)(((t_cmd *)my_cmd->content)->redirection))
			redrec = (t_redirection *)(((t_cmd *)my_cmd->content)->redirection->content);
		pipe(fd);
		if (bull_shit((t_cmd *) my_cmd->content))
			return;
		ft_after_expand(my_cmd);
		// if(!ft_strcmp((((t_cmd *)((my_cmd)->content))->after_expand)[0],"cd"))
		// cd_fuction((((t_cmd *)((my_cmd)->content))->after_expand)[1]);
		id = fork();
		if(id == 0)
		{
			if(my_cmd->next)
			{
				dup2(fd[1], 1);
				close(fd[1]);
			}
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
			if (save != -1)
			{
				dup2(save, 0);
				close(save);
			}
			if(redrec->e_type == INPUT)
			{
				dup2(redrec->fd, 0);
				close(redrec->fd);
			}
			run_cmd(env, (((t_cmd *)((my_cmd)->content))->after_expand));
			perror((((t_cmd *)((my_cmd)->content))->after_expand)[0]);
			exit(0);
		}
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
