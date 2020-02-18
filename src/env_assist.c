/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 08:00:50 by wanton            #+#    #+#             */
/*   Updated: 2020/02/17 12:48:14 by wanton           ###   ########.fr       */
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

int		len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*
**Function search name of the variable in env list,
**            index is returned, if the name is found
**			  -1 is returned, otherwise
*/

int		find_elem(char *elem, char **env)
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

char	*full_env_var(char *name, char **env)
{
	int		i;
	char	*res;

	if ((i = find_elem(name, env)) == -1)
		return ("");
	else if (!i)
		return (NULL);
	if (!(res = ft_strdup(env[i])))
		return (NULL);
	return (res);
}