/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_assist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 12:01:23 by wanton            #+#    #+#             */
/*   Updated: 2020/02/26 12:27:26 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function gets the value out of the env with name arg
** len - len of the name in arg
** name - part of a arg which overlapping with env
**       Returned: name if successful or NULL if error with allocated memory
*/

char	*get_value(int n, char **env, char *arg, int len)
{
	int		i;
	char	*name;
	char	*res;

	i = 0;
	if (!(name = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
		name[i++] = arg[n++];
	name[i] = '\0';
	if (!(res = take_env_elem(name, env)))
	{
		free(name);
		return (NULL);
	}
	free(name);
	return (res);
}

/*
**Function check the str for a ascii symbol
**       i (index of the ascii symbol) is returned, if successful
**		 -1 is returned, if symbol is not defined
*/

int		find_not_ascii(int i, char *str)
{
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (i);
		i++;
	}
	return (-1);
}

/*
**Function check the str for a $ symbol
**       i (index of the $) is returned, if successful
**		 -1 is returned, if symbol is not defined
*/

int		find_dollar(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i++] == '$')
			return (i);
	}
	return (-1);
}
