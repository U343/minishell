/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:23:49 by wanton            #+#    #+#             */
/*   Updated: 2020/01/30 08:20:14 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/param.h>

# include "libft.h"

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

/*
**Functions for run args
*/

int                 run_command(char **s_arg, char **env);
int					pwd_script(char **s_arg);
void				cd_script(char **s_arg, char **env);

/*
**Env functions
*/

int					add_elem(char *elem, char **env);
int					delete_elem(char *elem, char **env);
int					len_env(char **env);
char				*take_env_elem(char *name, char **env);
void				print_env(char **env);

#endif
