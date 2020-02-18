/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:30:04 by wanton            #+#    #+#             */
/*   Updated: 2020/02/18 15:16:37 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function for print error message
** s - function's name which was the reason of error
*/

static void	print_error(char *s)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putendl(s);
}

static int	change_env_param(char *param, char ***env)
{
	int 	i;
	char	*tmp;
	char	*res;
	char	*buf;

	if ((i = find_elem(param, *env)) != -1)
		free((*env)[i]);
	else
		i = len_env(*env);
	buf = NULL;
	if (!(res = getcwd(buf, MAXPATHLEN)))
		return (-1);
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(res) +
			ft_strlen(param) + 2))))
		return (-1);
	tmp = ft_strcpy(tmp, param);
	tmp = ft_strcat(tmp, "=");
	tmp = ft_strcat(tmp, res);
	(*env)[i] = tmp;
	free(buf);
	free(res);
	return (i);
}

static int	move_dir(char *arg, char ***env)
{
	int 	i;
	char	*tmp;

	if (!(tmp = full_env_var("OLDPWD", *env)))
		return (-1);
	if ((i = change_env_param("OLDPWD", env)) == -1)
		return (-1);
	if (chdir(arg) == -1)
	{
		if (access(arg, F_OK))
			print_error(arg);
		else if (access(arg, R_OK))
		{
			ft_putstr("cd: permission denied: ");
			ft_putendl(arg);
		}
		else
		{
			ft_putstr("cd: not a directory: ");
			ft_putendl(arg);
		}
		if (tmp[0])
		{
			free((*env)[i]);
			(*env)[i] = tmp;
		}
		else
			delete_elem("OLDPWD", *env);
	}
	else
	{
		if (tmp[0])
			free(tmp);
		if (change_env_param("PWD", env) == -1)
			return (-1);
	}
	return (0);
}

static int	cd_with_arg(char **s_arg, char ***env)
{
	int		i;
	char	*pth;
	char	*tmp;

	pth = NULL;
	if (ft_strcmp(s_arg[1], "-") == 0)
		pth = take_env_elem("OLDPWD", *env);
	else if (ft_strcmp(s_arg[1], "--") == 0)
		pth = take_env_elem("HOME", *env);
	else
		move_dir(s_arg[1], env);
	if (pth && pth[0])
	{
		if (!(tmp = full_env_var("OLDPWD", *env)))
			return (-1);
		if ((i = change_env_param("OLDPWD", env)) == -1)
			return (-1);
		if (chdir(pth) == -1)
		{
			print_error(pth);
			if (tmp[0])
			{
				free((*env)[i]);
				(*env)[i] = tmp;
			}
			else
				delete_elem("OLDPWD", *env);
		}
		else
		{
			if (tmp[0])
				free(tmp);
			if (change_env_param("PWD", env) == -1)
				return (-1);
		}
		free(pth);
	}
	return (0);
}

/*
** (pth = take_env_elem("HOME", *env))[0] because this function returned "" if
** env variable is not defined and then str[0] = '\0'
*/

int			cd_script(char **s_arg, char ***env)
{
	int		len;
	int 	i;
	char	*pth;
	char	*tmp;

	len = len_env(s_arg);
	if (len > 2)
		ft_putstr("cd: too many arguments\n");
	else if (len == 1)
	{
		if ((pth = take_env_elem("HOME", *env))[0])
		{
			if (!(tmp = full_env_var("OLDPWD", *env)))
				return (-1);
			if ((i = change_env_param("OLDPWD", env)) == -1)
				return (-1);
			if (chdir(pth) == -1)
			{
				print_error(pth);
				if (tmp[0])
				{
					free((*env)[i]);
					(*env)[i] = tmp;
				}
				else
					delete_elem("OLDPWD", *env);
			}
			else
			{
				if (tmp[0])
					free(tmp);
				if (change_env_param("PWD", env) == -1)
					return (-1);
			}
			free(pth);
		}
	}
	else if (len == 2)
		cd_with_arg(s_arg, env);
	return (0);
}
