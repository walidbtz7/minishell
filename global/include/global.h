/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/24 20:03:43 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

int		ft_strlen(char *str);
int		iswhite(int c);
int		istop(int c);
int		ft_isnumber(int c);
int		ft_isalnum(int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strldup(const char *s1, int len);
int		isimposter(int c);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, int start, int len);
char	*get_next_line(int fd);
char	**ft_split(char *s);
char	*charstr(char c);
void	fsingle(char c, int *single, int dbl);
void	fdbl(char c, int single, int *dbl);
#endif