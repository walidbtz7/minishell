/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:15:25 by mrafik            #+#    #+#             */
/*   Updated: 2022/09/28 19:21:38 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (5);
	if(!s2)
		return(0);
	while ((s1[i] != '\0') && (s2[i] != '\0'))
	{
		if(s1[i] == s2[i])
			i++;
	 	else
			break;
	}
	printf("i:%d 		size:%d\n",i,n);
	if(i == n )
		return(0);
	else
		return (69);
}
