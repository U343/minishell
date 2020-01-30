/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:31:27 by wanton            #+#    #+#             */
/*   Updated: 2020/01/30 07:57:34 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*take_env_elem(char *name, char **env)
{
	int		i;
	char 	*tmp;
	char	*res;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(name) + 2)))
		return (NULL);
	tmp = ft_strcpy(tmp, name);
	tmp = ft_strcat(tmp, "=");
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			res = ft_strdup((ft_strchr(env[i], '=') + 1));
			free(tmp);
			return (res);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

int 	find_elem(char *elem, char **env)
{
	int		i;
	char	*res;

	i = 0;
	if (!(*elem))
		return (-1);
	if (!(res = (char *)malloc(sizeof(char) * ft_strlen(elem) + 2)))
		return (-1);
	res = ft_strcpy(res, elem);
	res = ft_strcat(res, "=");
	while (env[i])
	{
		if (ft_strncmp(res, env[i], ft_strlen(res)) == 0)
		{
			free(res);
			return (i);
		}
		i++;
	}
	free(res);
	return (-1);
}

int		delete_elem(char *elem, char **env)
{
	int i;

	if ((i = find_elem(elem, env)) == -1)
		return (-1);
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	return (0);
}
// TODO по идее синал нужно будет размещать тут
int		add_elem(char *elem, char **env)
{
	int		len;
	char	*res;

	len  = len_env(env);
	if (!(res = ft_strdup(elem)))
		return (-1);
	env[len++] = res;
	env[len] = NULL;
	return (0);
}