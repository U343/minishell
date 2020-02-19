/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:30:04 by wanton            #+#    #+#             */
/*   Updated: 2020/02/19 17:00:47 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function for print error message
** s - function's name which was the reason of error
** flag - signal for format message: 0 - cd without args, 1 - with args
*/

static void	print_error(char *s, int flag)
{
	if (flag == 0)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(s);
	}
	else if (flag == 1)
	{
		if (access(s, F_OK))
			print_error(s, 0);
		else if (access(s, R_OK))
		{
			ft_putstr("cd: permission denied: ");
			ft_putendl(s);
		}
		else
		{
			ft_putstr("cd: not a directory: ");
			ft_putendl(s);
		}
	}
}

/*
**Function for run chdir and for check PWD and OLDPWD
** flag - variable for print_error()
**                  0 is returned, if successful
**                  -1 is returned, if error with allocate
*/

static int	start_move(char *pth, char ***env, int flag)
{
	int		i;
	char	*tmp;

	if (!(tmp = full_env_var("OLDPWD", *env)))
		return (-1);
	if ((i = change_env_param("OLDPWD", env)) == -1)
		return (-1);
	if (chdir(pth) == -1)
	{
		print_error(pth, flag);
		if (tmp[0])
		{
			free((*env)[i]);
			(*env)[i] = tmp;
		}
		else
			delete_elem("OLDPWD", *env);
		return (0);
	}
	if (tmp[0])
		free(tmp);
	if (change_env_param("PWD", env) == -1)
		return (-1);
	return (0);
}

/*
**Function call start_move()
**                  0 is returned, if successful
**                  -1 is returned, if error in start_move()
*/

static int	move_dir(char *arg, char ***env)
{
	if (start_move(arg, env, 1) == -1)
		return (-1);
	return (0);
}

/*
**Function for check argc of the cd
**                  0 is returned, if successful
**                  -1 is returned, if error with start_move()
*/

static int	cd_with_arg(char **s_arg, char ***env)
{
	char	*pth;

	pth = NULL;
	if (ft_strcmp(s_arg[1], "-") == 0)
		pth = take_env_elem("OLDPWD", *env);
	else if (ft_strcmp(s_arg[1], "--") == 0)
		pth = take_env_elem("HOME", *env);
	else
		move_dir(s_arg[1], env);
	if (pth && pth[0])
	{
		if (start_move(pth, env, 0) == -1)
			return (-1);
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
	char	*pth;

	len = len_env(s_arg);
	if (len > 2)
		ft_putstr("cd: too many arguments\n");
	else if (len == 1)
	{
		if ((pth = take_env_elem("HOME", *env))[0])
		{
			if (start_move(pth, env, 0) == -1)
				return (-1);
			free(pth);
		}
	}
	else if (len == 2)
	{
		if (cd_with_arg(s_arg, env) == -1)
			return (-1);
	}
	return (0);
}
