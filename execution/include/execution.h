/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/26 16:42:01 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

void run_cmd(char **env,char **av);
char *path(char **env,char *search);
char	**convert(t_cmd *my_cmd);
void ft_after_expand(t_node *my_cmd);
void ft_pipe(t_node *my_cmd,char **env);
void bull_shit(t_node *my_cmd) ;
char	**argvconvert(t_node *argv);

#endif