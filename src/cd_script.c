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

/*
**Function for print error message
** s - function's name which was the reason of error
*/

static void	print_error(char *s)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putendl(s);
}

static void	move_dir(char *arg)
{
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
	}
}

static void	cd_with_arg(char **s_arg, char ***env)
{
	char	*pth;

	if (ft_strcmp(s_arg[1], "-") == 0)
	{
		pth = take_env_elem("OLDPWD", *env);
		if (chdir(pth) == -1)
			print_error(pth);
		free(pth);
	}
	else if (ft_strcmp(s_arg[1], "--") == 0)
	{
		pth = take_env_elem("HOME", *env);
		if (chdir(pth) == -1)
			print_error(pth);
		free(pth);
	}
	else
		move_dir(s_arg[1]);
}

int			cd_script(char **s_arg, char ***env)
{
	int		len;
	char	*pth;

	len = len_env(s_arg);
	if (len > 2)
		ft_putstr("cd: too many arguments\n");
	else if (len == 1)
	{
		pth = take_env_elem("HOME", *env);
		if (chdir(pth) == -1)
			print_error(pth);
		free(pth);
	}
	else if (len == 2)
		cd_with_arg(s_arg, env);
	return (0);
}
