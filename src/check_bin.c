/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:21:31 by wanton            #+#    #+#             */
/*   Updated: 2020/02/04 14:23:16 by wanton           ###   ########.fr       */
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
		execve(path, arg, env);
	else if (pid < 0)
	{
		//free(path);
		ft_putstr("Error: failed to complete ");
		ft_putendl(path);
		free(path);
		return (-1);
	}
	wait(&pid);
	free(path);
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
				exe_command(adr, arg, env);
				clear_mass(pth);
				return (0);
			}
			free(adr);
		}
		clear_mass(pth);

	}
	else
	{
		if ((lstat(arg[0], &buf) != -1))
		{
			exe_command(arg[0], arg, env);
			return (0);
		}
	}
	ft_putstr("command not found\n");
	return (0);
}

