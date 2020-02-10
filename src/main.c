/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:17:39 by wanton            #+#    #+#             */
/*   Updated: 2020/02/10 10:49:13 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clear_mass(char **mass)
{
    size_t	i;

    i = 0;
    while (mass[i])
        free(mass[i++]);
    free(mass);
}

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
	while (read(0, &p->symbol, sizeof(char)) > 0)
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
	/*count = (count == 1 ? count : (count - 1));*/
	count = count - 1;
	str[count] = '\0';
    free_args(&head);
	return (str);
}

char 	**init_env(char **arg)
{
	int len;
	int i;
	char **res;

	i = 0;
	len = 0;
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

int		main(int ac, char **av, char** env)
{
	int     flag;
	char	*arg;
	char 	**s_arg;

	flag = 0;
	(void)av;
	(void)ac;
	if (!(env = init_env(env)))
		return (-1);
	/*print_env(env);*/
	while (flag == 0)
    {
        write(1, "$> ", 3);
        if (!(arg = read_arg()))
			return (-1);
		s_arg = ft_strsplit(arg, ' ');
		scan_env(s_arg, env);
        flag = run_command(s_arg, &env);
        clear_mass(s_arg);
        free(arg);
    }
	return (0);
}
