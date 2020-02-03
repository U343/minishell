/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:03:09 by wanton            #+#    #+#             */
/*   Updated: 2020/02/03 11:19:25 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	exit_script(char **arg, char **env)
{
	(void)arg;
	(void)env;
	return (-1);
}

void	get_commands(char *tmp[8])
{
	tmp[0] = "cd";
	tmp[1] = "echo";
	tmp[2] = "pwd";
	tmp[3] = "env";
	tmp[4] = "setenv";
	tmp[5] = "unsetenv";
	tmp[6] = "exit()";
	tmp[7] = NULL;
}

int		std_shell_command(char **s_arg, char **env)
{
	int 	i;
	int		(*builtin_func[7]) (char **, char **);
	char 	*commands[8];

	i = 0;
	builtin_func[0] = &cd_script;
	builtin_func[1] = &echo_script;
	builtin_func[2] = &pwd_script;
	builtin_func[3] = &env_script;
	builtin_func[4] = &setenv_script;
	builtin_func[5] = &unsetenv_script;
	builtin_func[6] = &exit_script;
	get_commands(commands);
	while (commands[i])
	{
		if ((ft_strcmp(s_arg[0], commands[i])) == 0)
			return ((*builtin_func[i])(s_arg, env));
		i++;
	}
	ft_putstr("command not found\n");
	return (0);
}

int     run_command(char **s_arg, char **env)
{
	if (s_arg[0])
		return (std_shell_command(s_arg, env));
	else
		return (0);
}
