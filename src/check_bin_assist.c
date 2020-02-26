/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bin_assist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 10:57:39 by wanton            #+#    #+#             */
/*   Updated: 2020/02/26 15:46:34 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function joins strings name and path,
**            adr (full_path) is returned, always
*/

char	*get_full_path(char *n, char *p)
{
	char	*adr;

	adr = (char *)malloc(sizeof(char) * (ft_strlen(n) + ft_strlen(p) + 2));
	adr = ft_strcpy(adr, p);
	adr = ft_strcat(adr, "/");
	adr = ft_strcat(adr, n);
	return (adr);
}

/*
**Function search symbol '/' in str,
**            1 is returned, if successful
**			  0 is returned, otherwise
*/

int		find_slash(char const *str)
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
