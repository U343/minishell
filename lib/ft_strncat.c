/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:33:11 by mjoss             #+#    #+#             */
/*   Updated: 2020/01/16 10:40:36 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char *tmp;

	tmp = s1;
	while (*s1)
		s1++;
	while (n)
	{
		*s1 = *s2;
		if (*s2 == '\0')
			return (tmp);
		s1++;
		s2++;
		n--;
	}
	*s1 = '\0';
	return (tmp);
}
