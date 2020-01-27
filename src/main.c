/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:17:39 by wanton            #+#    #+#             */
/*   Updated: 2020/01/27 10:44:47 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clear_mass(char **mass)
{
    size_t	i;

    i = 0;
    while (mass[i])
    {
        free(mass[i++]);
    }
    free(mass);
}

/*char    *list_filler(t_arg *head, int count)
{
    int     i;
    char    *str;
}*/

char    *read_arg()
{
	t_arg   *p;
	t_arg	*head;
	char	*str;
	int    	count;
	int		res;

	head = ft_create_elem();
	p = head;
	count = 0;
	while (read(1, &p->symbol, sizeof(char)) > 0)
	{
		count++;
		res = (int)(p->symbol);
		if (res == EOF || res == '\n')
			break;
		p->next = ft_create_elem();
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
	count = (count == 1 ? count : (count - 1));
	str[count] = '\0';
    //free_args(&head);
	return (str);
}

int		main(/*int ac, char **av*/)
{
	int     flag;
//	int     i;
	char	*arg;
	char 	**s_arg;

	flag = 1;
	while (flag)
    {
        write(1, "$> ", 2);
        arg = read_arg();
        s_arg = ft_strsplit(arg, ' ');
        /*i = 0;
        while (s_arg[i])
        {
            ft_putstr(s_arg[i++]);
            ft_putstr(", ");
        }*/
        //ft_putchar('\n');
        flag = run_command(s_arg);
        clear_mass(s_arg);
        free(arg);
    }
	return (0);
}
