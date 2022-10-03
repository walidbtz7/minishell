/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/10/03 22:16:16 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct execution
{
	char	**tmp2;
	int		e;
	int		x;
	int		i;
	int		len;
	int		y;
	char	**env;
	char	**export;
	char	**tmp;
}	t_ex;

void	run_cmd(char **env,char **av);
char	*path(char **env,char *search);
char	**convert(t_cmd *my_cmd);
void	ft_after_expand(t_node *my_cmd);
char	**ft_pipe(t_node *my_cmd,char **env);
int		*bull_shit(t_cmd *my_cmd) ;
char	**argvconvert(t_node *argv);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
void	ft_error(char **str);
int		cd_fuction(char *path, char **env);
void	herrdoc(t_redirection *redrec);
void	echo_function(char **str);
char	*path(char **env,char *search);
void	ft_directions(t_node *my_cmd, int *fd,int *lst_fd, int save);
char	**export_sort(char **envp);
char	**builtins(char **str,char **env);
char	**export_sort(char **envp);
char	**export_cmd(char **env,char **str);
int		ft_strlen2(char **str);

#endif