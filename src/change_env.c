/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:15:50 by wanton            #+#    #+#             */
/*   Updated: 2020/02/17 13:10:31 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_free_env(char **env, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

/*
**Function delete env variable with name elem
**            0 is returned, if successful
**            -1 is returned, if elem is not defined
*/

int		delete_elem(char *elem, char **env)
{
	int		i;
	char	*tmp;

	if ((i = find_elem(elem, env)) == -1)
		return (-1);
	tmp = env[i];
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	free(tmp);
	return (0);
}

/*
**Function add new variable in env list
**            0 is returned, if successful
**            -1 is returned, if error allocate memory
*/

int		new_elem(char *name, char *value, char **env, int len)
{
	char	*res;

	if (!(res = ft_strnew(ft_strlen(name) +
			ft_strlen(value) + 2)))
		return (-1);
	res = ft_strcpy(res, name);
	res = ft_strcat(res, "=");
	res = ft_strcat(res, value);
	env[len++] = res;
	env[len] = NULL;
	res = NULL;
	return (0);
}

/*
**Function copy env list with new cell for new elem
**            0 is returned, if successful
**            -1 is returned, if error allocate memory
*/

int		add_elem(char *name, char *value, char ***env)
{
	int		i;
	int		len;
	char	**new_env;

	i = 0;
	len = len_env(*env);
	if (!(new_env = (char **)malloc(sizeof(char *) * (len + 2))))
		return (-1);
	while (i < len)
	{
		if (!(new_env[i] = ft_strdup((*env)[i])))
		{
			error_free_env(new_env, i);
			return (-1);
		}
		i++;
	}
	if (new_elem(name, value, new_env, len) == -1)
	{
		error_free_env(new_env, i);
		return (-1);
	}
	clear_mass(*env);
	*env = new_env;
	return (0);
}
