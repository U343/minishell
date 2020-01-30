/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:30:04 by wanton            #+#    #+#             */
/*   Updated: 2020/01/30 08:51:44 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	len_arg(char **s_arg)
{
	int	i;

	i = 0;
	while (s_arg[i] != NULL)
	{
		i++;
	}
	return (i);
}

void 	cd_script(char **s_arg, char **env)
{
	int	len;

	len = len_arg(s_arg);
	if (len > 2) // TODO стандартный ls поддерживает 2 аргумента
		ft_putstr("cd: too many arguments");
	else if (len == 1)
		chdir(take_env_elem("HOME", env));
	else if (len == 2)
	{
		if (chdir(s_arg[1]) == -1)
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putstr(s_arg[1]);
		}
	}
}
