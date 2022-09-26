/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:46:43 by mrafik            #+#    #+#             */
/*   Updated: 2022/09/26 23:11:29 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_nodesize(t_node *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		node = node->next;
		i++;
	}
	return (i);
}

char	**argvconvert(t_node *argv)
{
	int		size;
	char	**str;
	char	*tmp;
	int		i;

	i = 0;
	if (!argv)
		return (NULL);
	size = ft_nodesize(argv);
	str = (char **)malloc((size + 1) * sizeof(char *));
	while (argv)
	{
		tmp = ((t_argv *)(argv->content))->value;
		str[i] = ft_strdup(tmp);
		argv = argv->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}
