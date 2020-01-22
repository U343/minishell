/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:57:32 by mjoss             #+#    #+#             */
/*   Updated: 2020/01/16 10:40:36 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long	tmp;

	tmp = n;
	if (n < 0)
	{
		ft_putchar('-');
		tmp *= -1;
	}
	if (tmp <= 9)
		ft_putchar(tmp + '0');
	else
	{
		ft_putnbr(tmp / 10);
		ft_putchar(tmp % 10 + '0');
	}
}
