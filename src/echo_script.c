/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:18:40 by wanton            #+#    #+#             */
/*   Updated: 2020/02/03 11:40:48 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	parse_flag(char **arg)
{
	int i;
	int j;

	i = 1;
	if (arg[i] == NULL)
		return (1);
	while (arg[i])
	{
		j = 1;
		if (arg[i][0] != '-')
			break ;
		while (arg[i][j])
		{
			if (arg[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int		echo_script(char **arg, char ***env)
{
	int i;

	(void)env;
	if ((i = parse_flag(arg)) == -1)
		return (0);
	while (arg[i])
	{
		ft_putstr(arg[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
