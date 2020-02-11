/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:31:27 by wanton            #+#    #+#             */
/*   Updated: 2020/02/11 12:46:15 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function to replace $NAME with env variable value
**       0 is returned if successful
**       -1 is returned if an error with allocated memory
*/

int 	scan_env(char **arg, char **env)
{
	int 	i;
	char 	*tmp;

	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '$')
		{
			tmp = arg[i];
			if ((arg[i] = take_env_elem(++arg[i], env)) == NULL)
				return (-1);
			free(tmp);
		}
		i++;
	}
	return (0);
}

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
	return ("");
}

int 	env_script(char **arg, char ***env)
{
	(void)arg;
	print_env(*env);
	return (0);
}

int 	setenv_script(char **arg, char ***env)
{
	if (!arg[1])
		ft_putstr("usage: setenv VAR [VALUE]\n");
	else if (!arg[2])
		ft_putstr("usage: setenv VAR [VALUE]\n");
	else if (arg[3])
		ft_putstr("setenv: too many arguments\n");
	else
	{
		if (find_elem(arg[1], *env) != -1)
		{
			ft_putstr("setenv: item already exists: ");
			ft_putendl(arg[1]);
		}
		else if (add_elem(arg[1], arg[2], env) == -1)
			return (-1);
	}
	return (0);
}

int 	unsetenv_script(char **arg, char ***env)
{
	if (!arg[1])
		ft_putstr("usage: unsetenv [NAME]\n");
	else if (arg[2])
		ft_putstr("unsetenv: too many arguments\n");
	else
	{
		if (delete_elem(arg[1], *env) == -1)
		{
			ft_putstr("setenv: name not defined: ");
			ft_putendl(arg[1]);
		}
	}
	return (0);
}