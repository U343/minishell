/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:21:31 by wanton            #+#    #+#             */
/*   Updated: 2020/02/07 10:52:39 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*get_full_path(char *name, char *path)
{
	char 	*adr;

	adr = (char *)malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(path) + 2));
	adr = ft_strcpy(adr, path);
	adr = ft_strcat(adr, "/");
	adr = ft_strcat(adr, name);
	return (adr);
}

int 	find_slash(char const *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '/')
			return (1);
	}
	return (0);
}

int 	exe_command(char *path, char **arg, char **env)
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

int 	check_bin(char **arg, char **env)
{
	struct stat	buf;
	char		**pth;
	char 		*adr;
	char 		*tmp;
	int			i;

	if (find_slash(arg[0]) == 0)
	{
		//ft_putstr("ok\n");
		i = 0;
		tmp = take_env_elem("PATH", env);
		if (!(pth = ft_strsplit(tmp,':')))
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
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
					return (0);
				}
				ft_putstr("msh: permission denied: ");
				ft_putendl(adr);
			}
			free(adr);
		}
		clear_mass(pth);

	}
	else
	{
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
	}
	ft_putstr("msh: command not found: ");
	ft_putendl(arg[0]);
	return (0);
}

