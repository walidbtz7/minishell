/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:30:36 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/26 23:39:57 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_count(char *s)
{
	int	i;
	int	stock;

	i = 0;
	stock = 0;
	while (iswhite(s[i]))
		i++;
	while (s[i])
	{
		if ((iswhite(s[i]) && !iswhite(s[i + 1])) && s[i + 1] != '\0')
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

void	init_tab(int	*tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
}

static int	ft_normi(char *s, char **str, int start)
{
	int	tab[5];

	init_tab(tab, 5);
	while (tab[0] <= ft_strlen(s))
	{
		fsingle(s[tab[0]], &tab[1], tab[2]);
		fdbl(s[tab[0]], tab[1], &tab[2]);
		if (!iswhite(s[tab[0]]) && tab[3] == 0)
		{
			start = tab[0];
			tab[3] = 1;
		}
		else if (((iswhite(s[tab[0]]) || \
		tab[0] == ft_strlen(s)) && tab[3] == 1) && \
		(tab[1] == 0 && tab[2] == 0))
		{
			str[tab[4]++] = ft_substr(s, start, (tab[0] - start));
			if (!str[tab[4] - 1])
				return (ft_free(tab[4] - 1, str));
			tab[3] = 0;
		}
		tab[0]++;
	}
	str[tab[4]] = NULL;
	return (1);
}

char	**ft_split_space(char *s)
{
	int		i;
	char	**str;

	if (s == NULL)
		return (0);
	str = (char **) malloc((ft_count(s) + 1) * sizeof(char *));
	if (!str)
		return (0);
	i = ft_normi(s, str, 0);
	if (i == 0)
		return (NULL);
	free(s);
	return (str);
}
