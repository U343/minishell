#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "lib/libft.h"

/*
**------------------------------------Struct------------------------------------
*/

typedef struct		s_arg
{
	char 			symbol;
	struct s_arg	*next;
}					t_arg;

/*
**-----------------------------------Function-----------------------------------
*/

/*
**Functions for list t_arg
*/

void				free_args(t_arg **arg);
void				print_list(t_arg *arg);
t_arg				*ft_create_elem(void);

#endif