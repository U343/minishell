/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:18:40 by wanton            #+#    #+#             */
/*   Updated: 2020/02/11 13:40:56 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
**Function for check flag -n
**       index is returned
*/

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
		if (arg[i][j] == '\0')
			return (++i);
		while (arg[i][j])
		{
			if (arg[i][j++] != 'n')
				return (i);
		}
		i++;
	}
	return (i);
}

/*
**The same as ft__putstr, but it is ignoring symbol "
**       0 is returned always (for list functions in run_command)
*/

void		ft_putstr_echo(char *s)
{
	int i;

	i = 0;
	if (s[i] == '"')
		i++;
	while (s[i] && s[i] != '"')
		ft_putchar(s[i++]);
}

/*
**My echo ignored flag -n
**       0 is returned always (for list functions in run_command)
*/

int			echo_script(char **arg, char ***env)
{
	int i;

	(void)env;
	if ((i = parse_flag(arg)) == -1)
		return (0);
	while (arg[i])
	{
		ft_putstr_echo(arg[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
