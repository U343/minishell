/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_assist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:36:17 by wanton            #+#    #+#             */
/*   Updated: 2020/02/18 15:36:17 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_env_param(char *param, char ***env)
{
	int 	i;
	char	*tmp;
	char	*res;
	char	*buf;

	if ((i = find_elem(param, *env)) != -1)
		free((*env)[i]);
	else
		i = len_env(*env);
	buf = NULL;
	if (!(res = getcwd(buf, MAXPATHLEN)))
		return (-1);
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(res) +
											   ft_strlen(param) + 2))))
		return (-1);
	tmp = ft_strcpy(tmp, param);
	tmp = ft_strcat(tmp, "=");
	tmp = ft_strcat(tmp, res);
	(*env)[i] = tmp;
	free(buf);
	free(res);
	return (i);
}
