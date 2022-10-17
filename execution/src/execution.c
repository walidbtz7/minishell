/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:26:50 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/17 16:23:42 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	herrdoc(t_redirection *redrec,char **env,int fd)
{
	char *str;
	t_cargv *dollar;
	int id;
	int status;
	id = fork();
	if(id == 0)
	{
		signal(SIGINT, SIG_DFL);
		str = readline("<");
		dollar = NULL;
		while (ft_strcmp(redrec->file,str))
		{
			dollar = init_cargv(str,env);
			if(redrec->expand == 1)
				str = expand_env(dollar);
			ft_putstr_fd(str,fd);
			write(fd, "\n", 1);
			free(str);
			str = readline("<");
		}
		close(fd);
		exit(0);
	}
	signal (SIGINT, SIG_IGN);
	int res = 0;
	while(res != -1)
	{
		res = waitpid(-1, &status, 0);
		if(WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			code = WTERMSIG(status) + 128;
		}
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	// close(fd);
}

int	*bull_shit(t_cmd *cmd,char **env)
{
	t_redirection	*red;
	t_node			*my_cmd = NULL;
	int				fd[2];
	int				x;
	int				*lst_fd;

	lst_fd = (int *)malloc(2 * sizeof (int));
	lst_fd[0]=-1;
	lst_fd[1] = -1;
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
			if (lst_fd[0] < 0)
					{
						perror(red->file);
						lst_fd[0] = -20;
						code = 1;
					}
		}
		if (red->e_type == OUTPUT)
		{
			if(lst_fd[1] > 0)
				close(lst_fd[1]);
			lst_fd[1] = open(red->file, O_CREAT | O_WRONLY , 0666);
			if (lst_fd[1] < 0)
				perror("red->file"); 
		}
		if (red->e_type == APPED)
		{
			if(x != 0)
				close(lst_fd[1]);
			lst_fd[1] = open(red->file, O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (lst_fd[1] < 0)
				perror("red->file");
		}
		if (red->e_type == HERRDOC)
		{
			if(x != 0)
				close(lst_fd[0]);
			pipe(fd);
			lst_fd[1] = fd[1];
			herrdoc(red,env,lst_fd[1]);
			lst_fd[0] = fd[0];
			x = 1;
		}
		my_cmd = my_cmd->next;
	}
	return(lst_fd);
}





void ft_after_expand(t_node *my_cmd)
{
	if(my_cmd)
		((t_cmd *)(my_cmd->content))->after_expand = argvconvert(((t_cmd *)my_cmd->content)->argv);
}

void ft_error(char **str)
{
	if(str)
	{
		if(ft_strchr(str[0],'/'))
		{
			if(!ft_strcmp(str[0],"/"))
			{
				ft_putstr_fd("minishell:  ",2);
				ft_putstr_fd(str[0], 2);
				ft_putstr_fd(": is a directory\n",2);
				exit(126);
			}
			else
			{
				ft_putstr_fd("minishell:  ",2);
				ft_putstr_fd(str[0], 2);
				ft_putstr_fd(": No such file or directory\n",2);
				exit(127);
			}
		}
		ft_putstr_fd("minishell:  ",2);
		ft_putstr_fd(str[0], 2);
		ft_putstr_fd(": command not found\n",2);
		exit(127);
	}
}
int ft_not_builts(char **str)
{
	if(str)
	{
		
		if(ft_strcmp(str[0],"echo") && ft_strcmp(str[0],"pwd")
	 		&& ft_strcmp(str[0],"export") && ft_strcmp(str[0],"unset") &&
	 		ft_strcmp(str[0],"exit") &&  ft_strcmp(str[0],"cd") && ft_strcmp(str[0],"env"))
			return(1);
	
		else
		return(0);
	}
	return(2);
}
void	ft_pipe(t_node *cmd,t_ex *ex)
{
	int fd[2];
	pid_t id;
	t_node *my_cmd;
	int save;
	int	*lst_fd;
	int i = 0;
	int status;
	int my_fd;
	t_redirection *redrec;
	
	my_cmd = cmd;
	save = -1;
	redrec = NULL;
	ft_after_expand(my_cmd);
	if(ft_lstsize(cmd) == 1 && !ft_not_builts((((t_cmd *)((my_cmd)->content))->after_expand)))
	{
		my_fd = dup(1);
		if(((t_cmd *)my_cmd->content)->redirection)
				redrec = (t_redirection *)(((t_cmd *)my_cmd->content)->redirection->content);
			lst_fd = bull_shit((t_cmd *)my_cmd->content,ex->env);
			if((((t_cmd *)((my_cmd)->content))->after_expand))
				ft_directions(my_cmd,fd,lst_fd,-20);
			builtins((((t_cmd *)((my_cmd)->content))->after_expand), ex,0);
			close(lst_fd[1]);
			close(lst_fd[0]);
			dup2(my_fd,1);
	}
	else
	{
		while (my_cmd)
		{
			if(((t_cmd *)my_cmd->content)->redirection)
				redrec = (t_redirection *)(((t_cmd *)my_cmd->content)->redirection->content);
			ft_after_expand(my_cmd);
			lst_fd = bull_shit((t_cmd *)my_cmd->content,ex->env);
			pipe(fd);
			id = fork();
			if(id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if((((t_cmd *)((my_cmd)->content))->after_expand))
						if(!ft_directions(my_cmd,fd,lst_fd,save))
							return;
				builtins((((t_cmd *)((my_cmd)->content))->after_expand), ex,1);
				if(ft_not_builts((((t_cmd *)((my_cmd)->content))->after_expand)) == 1)
				{
					run_cmd(ex->env, (((t_cmd *)((my_cmd)->content))->after_expand));
		 			ft_error((((t_cmd *)((my_cmd)->content))->after_expand));
				}
					exit(0);
			}
			signal (SIGINT, SIG_IGN);
		//signal
			i = 0;
			if((((t_cmd *)((my_cmd)->content))->after_expand))
			{	while ((((t_cmd *)((my_cmd)->content))->after_expand)[i])
					free((((t_cmd *)((my_cmd)->content))->after_expand)[i++]);
			free((((t_cmd *)((my_cmd)->content))->after_expand));
			}
			close(lst_fd[1]);
			close(lst_fd[0]);
			if(save != -1)
				close(save);
			close(fd[1]);
			save =  fd[0];
			(my_cmd) = (my_cmd)->next;
		}
		close(save);
	}
	int res = 0;
	while(res != -1)
	{
		res = waitpid(-1, &status, 0);
		if(WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			code = WTERMSIG(status) + 128;
		}
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	// WIFEXITED if  true \\ WEXITSTATUS number of exit status
	// WIFSIGNALED if true \\ ......... + 128 number of exit code
	// 285 pars err
}
