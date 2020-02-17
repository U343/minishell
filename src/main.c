/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:17:39 by wanton            #+#    #+#             */
/*   Updated: 2020/02/17 10:48:09 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function for print error message,
**if an error with allocated memory occurred
**            -1 is returned always (for save code style)
*/

static int	print_error(char *s)
{
	ft_putstr_fd("msh: memory allocation error: ", 2);
	ft_putendl(s);
	return (-1);
}

/*
**Function for copy list's content in array,
**            array is returned, if successful
**            NULL is returned if an error with allocated memory
*/

static char	*mass_filler(t_arg *head, int count)
{
	t_arg	*p;
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * count + 1)))
		return (NULL);
	p = head;
	while (p)
	{
		str[i++] = p->symbol;
		p = p->next;
	}
	i = i - 1;
	str[i] = '\0';
	return (str);
}

/*
**Function for read args from standard input,
**            array is returned, if successful (from mass_filler)
**            NULL is returned if an error with allocated memory
*/

static char	*read_arg(void)
{
	t_arg	*p;
	t_arg	*head;
	char	*str;
	int		count;
	int		res;

	if (!(head = ft_create_elem()))
		return (free_args(&head));
	p = head;
	count = 0;
	while (read(0, &p->symbol, sizeof(char)) > 0)
	{
		count++;
		res = (int)(p->symbol);
		if (res == EOF || res == '\n')
			break ;
		if (!(p->next = ft_create_elem()))
			return (free_args(&head));
		p = p->next;
	}
	str = mass_filler(head, count);
	free_args(&head);
	return (str);
}

/*
**Function for copy env variables in my allocated array.
**I can't access to memory in standard env
**            array is returned, if successful (from mass_filler)
**            NULL is returned if an error with allocated memory
*/

static char	**init_env(char **arg, int ac, char **av)
{
	int		len;
	int		i;
	char	**res;

	i = 0;
	len = 0;
	(void)av;
	(void)ac;
	while (arg[len])
		len++;
	if (!(res = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		res[i] = ft_strdup(arg[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int			main(int ac, char **av, char **env)
{
	int		flag;
	char	*arg;
	char	**s_arg;

	flag = 0;
	if (!(env = init_env(env, ac, av)))
		return (print_error("init_env"));
	while (flag == 0)
	{
		write(1, "$> ", 3);
		if (!(arg = read_arg()))
			return (print_error("read_arg"));
		if (!(s_arg = ft_strsplit(arg, ' ')))
		{
			free(arg);
			return (print_error("ft_strsplit"));
		}
		if (scan_env(s_arg, env) == -1)
			return (print_error("scan_env"));
		flag = run_command(s_arg, &env);
		clear_mass(s_arg);
		free(arg);
	}
	return (0);
}
