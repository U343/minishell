/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:03:09 by wanton            #+#    #+#             */
/*   Updated: 2020/02/17 13:47:21 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function to exit the minishell
*/

int		exit_script(char **arg, char ***env)
{
	(void)arg;
	(void)env;
	return (-1);
}

/*
**Function add names of the standard commands in array tmp
*/

void	get_commands(char *tmp[9])
{
	tmp[0] = "cd";
	tmp[1] = "echo";
	tmp[2] = "pwd";
	tmp[3] = "env";
	tmp[4] = "setenv";
	tmp[5] = "unsetenv";
	tmp[6] = "exit()";
	tmp[7] = "test";
	tmp[8] = NULL;
}

/*
**Function check arg,
**if arg[0] is standard command, then run him
**otherwise run check_bin()
**            0 is returned, if successful
**            -1 is returned, if error with one of the builtin_func or if run
**                            exit_script()
*/

int		std_shell_command(char **s_arg, char ***env)
{
	int		i;
	int		(*builtin_func[8]) (char **, char ***);
	char	*commands[9];

	i = 0;
	builtin_func[0] = &cd_script;
	builtin_func[1] = &echo_script;
	builtin_func[2] = &pwd_script;
	builtin_func[3] = &env_script;
	builtin_func[4] = &setenv_script;
	builtin_func[5] = &unsetenv_script;
	builtin_func[6] = &exit_script;
	builtin_func[7] = &exit_script;
	get_commands(commands);
	while (commands[i])
	{
		if ((ft_strcmp(s_arg[0], commands[i])) == 0)
			return ((*builtin_func[i])(s_arg, env));
		i++;
	}
	return (check_bin(s_arg, *env));
}

/*
**Function check arg,
**            0 is returned, if arg exists
**			  otherwise, return value of std_shell_commands()
*/

int		run_command(char **s_arg, char ***env)
{
	if (s_arg[0])
		return (std_shell_command(s_arg, env));
	else
		return (0);
}
