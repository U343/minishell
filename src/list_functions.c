/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:22:12 by wanton            #+#    #+#             */
/*   Updated: 2020/02/11 11:48:22 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg		*ft_create_elem(void)
{
	t_arg *tmp;

	if (!(tmp = malloc(sizeof(t_arg))))
		return (NULL);
	tmp->symbol = 0;
	tmp->next = NULL;
	return (tmp);
}

void		print_list(t_arg *arg)
{
	t_arg	*p;

	p = arg;
	while (p)
	{
		write(1, &p->symbol, 1);
		ft_putchar(' ');
		p = p->next;
	}
	ft_putchar('\n');
}

void    clear_mass(char **mass)
{
	size_t i;

	i = 0;
	while (mass[i])
		free(mass[i++]);
	free(mass);
}

char		*free_args(t_arg **arg)
{
	t_arg	*p;
	t_arg	*tmp;

	if (arg && *arg)
	{
		p = *arg;
		while (p)
		{
			tmp = p->next;
			free(p);
			p = tmp;
		}
	}
	return (NULL);
}
