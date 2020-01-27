/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 22:34:37 by mjoss             #+#    #+#             */
/*   Updated: 2020/01/27 11:25:40 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*tmp;

	if (size + 1 == 0)
		return (NULL);
	tmp = (char*)malloc((size + 1) * sizeof(char));
	if (tmp)
	{
		while (size + 1)
		{
			tmp[size] = 0;
			size--;
		}
		return (tmp);
	}
	return (NULL);
}
