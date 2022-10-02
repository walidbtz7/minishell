/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wboutzou <wboutzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:02 by wboutzou          #+#    #+#             */
/*   Updated: 2022/10/02 00:49:42 by wboutzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_txt(t_node **argv, t_token *token, char **envp)
{
	t_cargv	*check;
	t_node	*new;
	char	**str;
	int		i;

	i = 0;
	check = init_cargv(token->value, envp);
	if (!check)
		return ;
	str = fargv(check);
	if (str)
	{
		while (str[i])
		{
			if (str[i])
			{
				check = init_cargv(str[i], envp);
				new = ft_lstnew(init_argv(rmquote(check)));
				ft_nodeadd_back(argv, new);
			}
			i++;
		}
	}
	free(str);
}
