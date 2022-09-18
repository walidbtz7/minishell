/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:30:36 by wboutzou          #+#    #+#             */
/*   Updated: 2022/09/18 15:39:46 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global.h"

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
		if (iswhite(s[i])&& !iswhite(s[i + 1]) && s[i + 1] != '\0')
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

void fsingle(char c, int *single, int dbl)
{
    if(dbl == 0)
    {
        if(c == 39 && *single == 0)
            *single = 1;
        else if(c == 39 && *single == 1)
            *single = 0;
    }
}

void fdbl(char c, int single, int *dbl)
{
    if(single == 0)
    {
        if(c == 34 && *dbl == 0)
            *dbl = 1;
        else if(c == 34 && *dbl == 1)
            *dbl = 0;
    }
}

static int	ft_normi(char *s, char **str, int start)
{
	int		t;
	int		j;
	int     i;
	int single;
	int dbl;
	i = 0;
	t = 0;
	j = 0;
	single = 0;
	dbl = 0;
	while (i <= ft_strlen(s))
	{
		fsingle(s[i],&single, dbl);
		fdbl(s[i], single, &dbl);
		if (!iswhite(s[i]) && t == 0)
		{
			start = i;
			t = 1;
		}
		else if (((iswhite(s[i]) || i == ft_strlen(s)) && t == 1) && (single == 0 && dbl == 0))
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

char	**ft_split(char *s)
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
	return (str);
}
