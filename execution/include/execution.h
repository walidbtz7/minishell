/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:30:51 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/20 00:35:36 by mrafik           ###   ########.fr       */
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
	char	**ex_save;
}	t_ex;

void	run_cmd(char **env, char **av);
char	*path(char **env, char *search);
char	**convert(t_cmd *my_cmd);
void	ft_after_expand(t_node *my_cmd);
void	ft_execution(t_node *my_cmd, t_ex *ex);
int		*bull_shit(t_cmd *my_cmd, char **env,int *d);
char	**argvconvert(t_node *argv);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
void	ft_error(char **str);
char	**cd_fuction(char *path, char **env, int d);
void	echo_function(char **str);
char	*path(char **env, char *search);
int		ft_directions(t_node *my_cmd, int *fd, int *lst_fd, int save);
char	**export_sort(char **envp);
void	builtins(char **str, t_ex *ex, int in);
char	**export_sort(char **envp);
void	 export_cmd(char **str, t_ex *ex);
int		ft_strlen2(char **str);
char	**ft_dup(char **str);
void	ft_free_e(char **str);
void	befor_cd(char **str, t_ex *ex);
int		ft_lstsize(t_node *a);
char	*ft_strjoin98(char *s1, char *s2);
void	wait_for_herrdoc(int *d);
void	herrdoc(t_redirection *redrec, char **env, int fd,int *d);
int		*in_out(t_redirection *red, int *lst_fd);
int		*apped_herr(t_redirection *red, int *lst_fd, char **env,int *d);
int		ft_nblt(char **str);
void	ft_error(char **str);
void	ft_norm1(t_node *my_cmd, t_ex *ex);
int		ft_close_free(t_node *my_cmd, int *lst_fd, int save, int *fd);
void	ft_sigdftl(void);
void	comd(t_node *my_cmd, t_ex *ex);
void	print2d(t_ex *ex);
int		check_cmd_export(char *str);
int		ft_search1(char *str, char *exp);
int		ft_strcmp3(char **env, char *str);
int		ft_help_env(char **env, char **str, t_ex *expo, int x);
void	ft_stock(t_ex *expo, char ***env, char **str, int x);
int		ft_strlen2(char **str);
void	sort_help(char **envp, int i);
char	**export_sort(char **exp);
int		ft_notvalid(char *str);
int		ft_help_save(char **env, char **str, t_ex *expo, int x);
void	ft_stock_save(t_ex *expo, char ***env, char **str, int x);
char	**ft_add(char	**export);
char	*ft_help_add(t_ex *ex, char **export);
int		ft_close(t_ex *ex, char **export);
int		ft_end(t_ex *ex, char **export);
int		position(char **env, char *search);
void	cd_update(char **env);
char	**cd_fuction(char *path_cd, char **env, int d);
int		check_echo(char **str);
void	echo_function(char **str);
void	remov_var_helper(char **env, char **retu, int x, int j);
char	**remove_var(char **env, int x);
char	**unset_helper(char **str, int z, char **env);
char	**ft_unset(char **env, char **str);
void	exit_err(char **str);
void	ft_exit(char **str, int in);
int		ft_atoi(const char *str);
#endif