/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/21 21:47:28 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H
# define ARGV_H

typedef struct cargv
{
	char	*src;
	char	c;
	int		i;
	char	**envp;
	int		start;
	int		single;
	int		expand;
	int		dbl;
}	t_cargv;

char	**fargv(t_cargv *check);
t_cargv	*init_cargv(char *src, char **envp);
void	cargv_advence(t_cargv *cargv);
void	single_quote(t_cargv *cargv);
void	double_quote(t_cargv *cargv);
char	*expandenv(t_cargv *cargv);
char	*rmquote(t_cargv *check);
#endif