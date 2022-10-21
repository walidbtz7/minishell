/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrafik <mrafik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 22:58:47 by mrafik            #+#    #+#             */
/*   Updated: 2022/10/18 14:49:18 by mrafik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cont(char *stock)
{
	int	i;

	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	return (i);
}

char	*stockline(char *stock, char *buffer, int rd, int fd)
{
	while (rd > 0 && !ft_strchr(buffer, '\n'))
	{
		rd = read(fd, buffer, 1);
		if (rd < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[rd] = '\0';
		stock = ft_strjoin(stock, buffer);
	}
	free(buffer);
	if (rd == 0 && stock[0] == '\0')
	{
		free(stock);
		stock = NULL;
		return (0);
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	int			rd;
	char		*buffer;
	static char	*stock;
	int			i;
	char		*tmp;

	rd = 1;
	if (fd < 0)
		return (0);
	buffer = (char *) malloc(2);
	buffer[0] = 0;
	stock = stockline(stock, buffer, rd, fd);
	if (!stock)
		return (NULL);
	i = cont(stock);
	buffer = ft_substr(stock, 0, i + 1);
	tmp = stock;
	stock = ft_substr(stock, i + 1, ft_strlen(stock));
	free(tmp);
	return (buffer);
}
