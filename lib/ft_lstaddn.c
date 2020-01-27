/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:17:12 by mjoss             #+#    #+#             */
/*   Updated: 2020/01/16 10:40:36 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddn(t_list **lst, t_list *new, size_t n)
{
	t_list	*tmp;

	if ((n - 1) >= ft_lstsize(*lst))
		ft_lstaddend(lst, new);
	else
	{
		tmp = ft_lst_n(*lst, n);
		new->next = tmp->next;
		tmp->next = new;
	}
}
