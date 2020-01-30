/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_script.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:57:44 by wanton            #+#    #+#             */
/*   Updated: 2020/01/30 11:54:54 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	pwd_script(char **s_arg)
{
	char *buf;
	char *res;

	buf = NULL;
	if (s_arg[1] != NULL)
	{
		ft_putstr("pwd: too many arguments\n");
		return (0);
	}
	if (!(res = getcwd(buf, MAXPATHLEN)))
		return (-1);
	ft_putstr(res);
	ft_putchar('\n');
	free(buf);
	free(res);
	return (0);
}
