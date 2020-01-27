/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:03:09 by wanton            #+#    #+#             */
/*   Updated: 2020/01/27 13:20:46 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     run_command(char **s_arg)
{
    if ((ft_strcmp(s_arg[0], "exit()")) == 0)
        return (-1);
	else if ((ft_strcmp(s_arg[0], "pwd")) == 0)
	{
		if (s_arg[1] == NULL)
		{
			if (pwd_script() == -1)
				return (-1);
		}
		else
			ft_putstr("pwd: too many arguments\n");
 	}
	return (0);
}