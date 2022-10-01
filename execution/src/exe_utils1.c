/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:43:08 by mrafik            #+#    #+#             */
/*   Updated: 2022/09/30 22:32:27 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
int check_echo(char **str)
{
	int i;
	
	i = 1;
	while (str[1][i])
	{
		if(str[1][0] != '-')
			return(0);
		if(str[1][i] != 'n')
			return(0);
		i++;
	}
return(1);

}
void ft_directions(t_node *my_cmd, int *fd, int *lst_fd, int save)
{
	t_redirection *redrec;
	
	redrec = NULL;
	if(((t_cmd *)my_cmd->content)->redirection)
	{
		redrec = (t_redirection *)(((t_cmd *)my_cmd->content)->redirection->content);
	}
	if(my_cmd->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if(redrec != NULL)
	{
		if(redrec->e_type == OUTPUT)
		{
			dup2(lst_fd[1], 1);
			close(lst_fd[1]);
		}
		if(redrec->e_type == APPED)
		{
			dup2(lst_fd[1], 1);
			close(lst_fd[1]);
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
			dup2(lst_fd[0],0);
			close(lst_fd[0]);
		}
		if(redrec->e_type == INPUT)
		{
			dup2(lst_fd[0], 0);
			close(lst_fd[0]);
		}
	}
}
void	echo_function(char **str)
{
	int i;

	i = 1;
	if(check_echo(str))
		i = 2;
	while (str[i])
	{
		printf("%s %d",str[i],i);
		i++;
	}
	if(!check_echo(str))
		printf("\n");
}
void run_cmd(char **env,char **av)
{
	char *cmd_path;
	char *cmd;

	if(!av)
		return;
	cmd = ft_strjoin_free(ft_strdup("/"), av[0]);
	cmd_path = avai_path(path(env, "PATH"), cmd);
	free(cmd);
	execve(cmd_path,av, env);
}