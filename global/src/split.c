/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:30:36 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/16 09:50:40 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

static int	ft_count(char *s, char c)
{
	int	i;
	int	stock;

	i = 0;
	stock = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			stock++;
		i++;
	}
	return (stock + 1);
}

static int	ft_free(int j, char **str)
{
	while (j >= 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
	return (0);
}

static int	ft_normi(char *s, char c,	char **str, int start)
{
	int		t;
	int		j;
	int     i;

	i = 0;
	t = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && t == 0)
		{
			start = i;
			t = 1;
		}
		else if ((s[i] == c || i == ft_strlen(s)) && t == 1)
		{
			str[j++] = ft_substr(s, start, (i - start));
			if (!str[j - 1])
				return (ft_free(j - 1, str));
			t = 0;
		}
		i++;
	}
	str[j] = NULL;
	return (1);
}

char	**ft_split(char *s, char c)
{
	int		i;
	char	**str;

	if (s == NULL)
		return (0);
	str = (char **) malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	i = ft_normi(s, c, str, 0);
	if (i == 0)
		return (NULL);
	return (str);
}
