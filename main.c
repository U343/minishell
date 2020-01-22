/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:17:39 by wanton            #+#    #+#             */
/*   Updated: 2020/01/22 16:43:16 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *read_arg()
{
	t_arg  *p;
	t_arg	*head;
	char	*str;
	int    	count;
	int		res;

	p = ft_create_elem();
	head = p;
	count = 0;
	while (read(1, &p->symbol, sizeof(char)) > 0)
	{
		p->next = ft_create_elem();
		count++;
		res = (int)(p->symbol);
		if (res == EOF || res == '\n')
			break;
		p = p->next;
	}
	//write(1, "Ok\n", 3);
	//print_list(head);
	str = (char *)malloc(sizeof(char) * count + 1);
	count = 0;
	p = head;
	while (p)
	{
		str[count++] = p->symbol;
		p = p->next;
	}
	str[count] = '\0';
	return (str);
}

int		main(/*int ac, char **av*/)
{
	//pid_t	pid;
	char	*arg;

	write(1, "> ", 2);
	arg = read_arg();
	/*pid = fork();
	if (pid == -1)
		write(1, "Error\n", 6);
	else if (pid == 0)
		execv(arg, av);
	else
		wait(0);*/
	return (0);
}
