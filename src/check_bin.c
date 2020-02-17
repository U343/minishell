/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:21:31 by wanton            #+#    #+#             */
/*   Updated: 2020/02/17 12:02:36 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Split of the PATH on list names,
**            NULL is returned, if error with allocated memory
**			  char ** is returned, if successful
*/

static char	**split_path(char **env)
{
	char	*tmp;
	char	**pth;

	tmp = take_env_elem("PATH", env);
	if (!(pth = ft_strsplit(tmp, ':')))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (pth);
}

/*
**Fork function create new process and execve run binary file,
**            1 is returned, if successful
**			  -1 is returned, otherwise
*/

static int	exe_command(char *path, char **arg, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, arg, env) == -1)
		{
			ft_putstr("msh: exec format error: ");
			ft_putendl(path);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		ft_putstr("msh: failed to complete: ");
		ft_putendl(path);
		return (-1);
	}
	wait(&pid);
	return (1);
}

/*
**Function search bin file in the PATH and run it, if file is valid,
**            1 is returned, if file valid
**			  0 is returned, otherwise
*/

static int	check_in_path(char **arg, char **env, int i)
{
	struct stat	buf;
	char		**pth;
	char		*adr;

	if (!(pth = split_path(env)))
		return (-1);
	while (pth[i])
	{
		adr = get_full_path(arg[0], pth[i++]);
		if (lstat(adr, &buf) == 0)
		{
			if ((S_ISREG(buf.st_mode) && (buf.st_mode & S_IXUSR)))
			{
				exe_command(adr, arg, env);
				free(adr);
				clear_mass(pth);
				return (1);
			}
			ft_putstr("msh: permission denied: ");
			ft_putendl(adr);
		}
		free(adr);
	}
	clear_mass(pth);
	return (0);
}

/*
**Function check bin file's address and run it, if file is valid,
**            0 is returned, if file valid
**			  1 is returned, otherwise
*/

static int	check_adr(char **arg, char **env)
{
	struct stat	buf;

	if ((lstat(arg[0], &buf) != -1))
	{
		if ((S_ISREG(buf.st_mode) && (buf.st_mode & S_IXUSR)))
		{
			if (access(arg[0], F_OK) == 0)
				exe_command(arg[0], arg, env);
			else
			{
				ft_putstr("msh: exec format error: ");
				ft_putendl(arg[0]);
			}
			return (0);
		}
		ft_putstr("msh: permission denied: ");
		ft_putendl(arg[0]);
		return (0);
	}
	return (1);
}

int			check_bin(char **arg, char **env)
{
	int			res;

	if (find_slash(arg[0]) == 0)
	{
		res = check_in_path(arg, env, 0);
		if (res == -1)
			return (-1);
		else if (res == 1)
			return (0);
	}
	else
	{
		res = check_adr(arg, env);
		if (res == 0)
			return (0);
	}
	ft_putstr("msh: command not found: ");
	ft_putendl(arg[0]);
	return (0);
}
