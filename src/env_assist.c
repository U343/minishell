/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 08:00:50 by wanton            #+#    #+#             */
/*   Updated: 2020/02/07 12:25:13 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i++]);
		ft_putchar('\n');
	}
}

int 	len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
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
	free(env[i]);
	env[i] = NULL;
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	return (0);
}
// TODO по идее синал нужно будет размещать тут
int		add_elem(char *name, char *value, char **env)
{
	int		len;
	char	*res;

	len  = len_env(env);
	if (!(res = ft_strnew(ft_strlen(name) +
			ft_strlen(value) + 2)))
		return (-1);
	res = ft_strcat(res, name);
	res = ft_strcat(res ,"=");
	res = ft_strcat(res, value);
	env[len++] = res;
	env[len] = NULL;
	return (0);
}