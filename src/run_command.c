/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:03:09 by wanton            #+#    #+#             */
/*   Updated: 2020/01/30 08:36:03 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_elem(char **s_arg, char **env)
{
	char 	*tmp;

	tmp = take_env_elem(s_arg[1], env);
	ft_putstr(tmp);
	ft_putchar('\n');
	free(tmp);
}

int     run_command(char **s_arg, char **env)
{
    if ((ft_strcmp(s_arg[0], "exit()")) == 0)
        return (-1);
	else if ((ft_strcmp(s_arg[0], "pwd")) == 0)
	{
		if (pwd_script(s_arg) == -1)
			return (-1);
 	}
	else if ((ft_strcmp(s_arg[0], "cd")) == 0)
		cd_script(s_arg, env);
	else if ((ft_strcmp(s_arg[0], "env")) == 0)
		print_env(env);
	else if ((ft_strcmp(s_arg[0], "setenv")) == 0)
		add_elem(s_arg[1], env);
	else if ((ft_strcmp(s_arg[0], "unsetenv")) == 0)
		delete_elem(s_arg[1], env);
	else if ((ft_strcmp(s_arg[0], "take")) == 0)
		take_elem(s_arg, env);
	else
	{
		ft_putstr("zsh: command not found: ");
		ft_putstr(s_arg[0]);
		ft_putchar('\n');
	}
	return (0);
}