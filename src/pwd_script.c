/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_script.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:57:44 by wanton            #+#    #+#             */
/*   Updated: 2020/02/17 12:39:27 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**getcwd() allocate memory for res and buf
**              0 is returned, if successful
**              -1 is returned, if error with getcwd()
*/

int	pwd_script(char **s_arg, char ***env)
{
	char *buf;
	char *res;

	(void)env;
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
