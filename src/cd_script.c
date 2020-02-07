/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:30:04 by wanton            #+#    #+#             */
/*   Updated: 2020/02/07 13:23:20 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	len_arg(char **s_arg)
{
	int	i;

	i = 0;
	while (s_arg[i] != NULL)
		i++;
	return (i);
}

int 	change_env(char *pth, char **env, int st) // TODO add elem use malloc
{
	char	*tmp;
	char 	*foo;

	if (st == 1)
	{
		if (!(tmp = take_env_elem("PWD", env)))
			return (-1);
		ft_putendl(tmp);
		delete_elem("OLDPWD", env);
		delete_elem("PWD", env);
		add_elem("OLDPWD", tmp, env);
		add_elem("PWD", pth, env);
		free(tmp);
	}
	/*else if (st == 2)
	{
		if (!(tmp = take_env_elem("PWD", env)))
			return (-1);
		if (!(foo = take_env_elem("OLDPWD", env)))
			return (-1);
		delete_elem("OLDPWD", env);
		delete_elem("PWD", env);
		add_elem("OLDPWD", tmp, env);
		add_elem("PWD", foo, env);
		free(tmp);
		free(foo);
	}*/
	else if (st == 2)
	{
		if (!(tmp = take_env_elem("PWD", env)))
			return (-1);
		delete_elem("OLDPWD", env);
		delete_elem("PWD", env);
		add_elem("OLDPWD", tmp, env);
		free(tmp);
		if (!(foo = getcwd(tmp, MAXPATHLEN)))
			return (-1);
		add_elem("PWD", foo, env);
		free(tmp);
		free(foo);
	}
	return (0);
}

int 	cd_script(char **s_arg, char **env)
{
	int		len;
	char	*pth;

	len = len_arg(s_arg);
	if (len > 2)
		ft_putstr("cd: too many arguments\n");
	else if (len == 1) // OLDPWD == PWD ? OLDPWD : PWD;  PWD = HOME
	{
		pth = take_env_elem("HOME", env);
		chdir(pth);
		if (change_env(pth, env, 1) != 0)
			return (-1);
		free(pth);
	}
	else if (len == 2)
	{
		if (ft_strcmp(s_arg[1], "-") == 0)
		{ // d = PWD; PWD = OLDPWD; OLDPWD = d
			pth = take_env_elem("OLDPWD", env);
			if (change_env(pth, env, 1) != 0)
				return (-1);
			chdir(pth);
			free(pth);
		}
		else if (chdir(s_arg[1]) == -1)
		{ // OLDPWD = PWD; PWD = getcwd
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(s_arg[1]);
		}
		else
		{
			if (change_env(NULL, env, 2) != 0)
				return (-1);
		}
	}
	return (0);
}
