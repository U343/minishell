/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_tilda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:05:24 by wanton            #+#    #+#             */
/*   Updated: 2020/02/26 13:56:53 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function create new arg and replace ~ on the HOME,
**            0 is returned, if successful
**			  -1 is returned, if error with allocate memory
*/

static int	change_arg(char **env, char **arg)
{
	char	*tmp;
	char	*res;
	char	*s;

	s = *arg;
	if ((tmp = take_env_elem("HOME", env)) == NULL)
		return (-1);
	if (!(res = (char *)malloc(sizeof(char) * (ft_strlen(s) +
			ft_strlen(tmp)))))
		return (-1);
	res = ft_strcpy(res, tmp);
	res = ft_strcat(res, ++s);
	*arg = res;
	if (tmp[0])
		free(tmp);
	return (0);
}

/*
**Function checks arg for symbol ~,
**            0 is returned, if successful
**			  -1 is returned, if error with allocate memory
*/

int			scan_tilda(char **arg, char **env, int j)
{
	char	*tmp;

	j = -1;
	while (arg[++j])
	{
		if (arg[j][0] && arg[j][0] == '~')
		{
			if (!arg[j][1] || arg[j][1] == '/')
			{
				tmp = arg[j];
				if (change_arg(env, &arg[j]) == -1)
					return (-1);
				free(tmp);
			}
			else if (arg[j][1] && (ft_isalpha(arg[j][1]) ||
			ft_isdigit(arg[j][1])))
			{
				tmp = arg[j];
				if (!(arg[j] = ft_strdup(++arg[j])))
					return (-1);
				free(tmp);
			}
		}
	}
	return (0);
}
