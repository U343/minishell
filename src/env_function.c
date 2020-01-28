/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:31:27 by wanton            #+#    #+#             */
/*   Updated: 2020/01/28 14:11:12 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// TODO привести это в порядок
int 	find_elem(char *elem, char **env)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strcat(elem, "=");
	while (env[i])
	{
		if (ft_strncmp(res, env[i], ft_strlen(res)) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int 	len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
// TODO привести это в порядок
void	delete_elem(char *elem, char **env)
{
	int i;

	i = find_elem(elem, env);
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

// TODO привести это в порядок
void	add_elem(char *elem, char **env)
{
	int		len;
	char	*res;

	len  = len_env(env);
	res = ft_strdup(elem);
	env[len++] = res;
	env[len] = NULL;
}