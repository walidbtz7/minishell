/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:52 by wboutzou          #+#    #+#             */
/*   Updated: 2022/10/07 14:31:05 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

int		ft_strlen(char *str);
int		iswhite(int c);
int		istop(int c);
int		ft_isnumber(int c);
int		ft_isalnum(int c);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strldup(const char *s1, int len);
int		isimposter(int c);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, int start, int len);
char	*get_next_line(int fd);
char	**ft_split_space(char *s);
char	**ft_split(char const *s, char c);
char	*charstr(char c);
void	fsingle(char c, int *single, int dbl);
void	fdbl(char c, int single, int *dbl);
char	*ft_itoa(int n);
#endif