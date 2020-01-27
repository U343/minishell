/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_script.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:57:44 by wanton            #+#    #+#             */
/*   Updated: 2020/01/27 13:21:21 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	pwd_script(void)
{
	char *buf;
	char *res;

	buf = NULL;
	if (!(res = getcwd(buf, MAXPATHLEN)))
		return (-1);
	ft_putstr(res);
	ft_putchar('\n');
	return (0);
}