/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:23:49 by wanton            #+#    #+#             */
/*   Updated: 2020/02/04 14:21:18 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/param.h>

# include "libft.h"

/*
**-----------------------------------Struct-------------------------------------
*/

typedef struct		s_arg
{
	char 			symbol;
	struct s_arg	*next;
}					t_arg;

/*
**----------------------------------Functions-----------------------------------
*/

/*
**Functions for **lst
*/

void				clear_mass(char **mass);

/*
**Functions for binary files
*/

int					check_bin(char **arg, char **env);

/*
**Functions for list t_arg
*/

void				free_args(t_arg **arg);
void				print_list(t_arg *arg);
t_arg				*ft_create_elem(void);

/*
**Built-in shell commands
*/

int                 run_command(char **s_arg, char **env);
int					pwd_script(char **s_arg, char **env);
int					cd_script(char **s_arg, char **env);
int					echo_script(char **arg, char **env);
int					env_script(char **arg, char **env);
int					setenv_script(char **arg, char **env);
int					unsetenv_script(char **arg, char **env);
int					exit_script(char **arg, char **env);

/*
**Env functions
*/

int					add_elem(char *name, char *value, char **env);
int					scan_env(char **arg, char **env);
int					delete_elem(char *elem, char **env);
int					len_env(char **env);
char				*take_env_elem(char *name, char **env);
void				print_env(char **env);

#endif
