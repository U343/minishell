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

static	void	print_error(char *s)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putendl(s);
}

int 	cd_script(char **s_arg, char ***env)
{
	int		len;
	char	*pth;

	len = len_arg(s_arg);
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
	{
		if (ft_strcmp(s_arg[1], "-") == 0)
		{
			pth = take_env_elem("OLDPWD", *env);
			if (chdir(pth) == -1)
				print_error(pth);
			free(pth);
		}
		else if (chdir(s_arg[1]) == -1)
			print_error(s_arg[1]);
	}
	return (0);
}
