/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:23:49 by wanton            #+#    #+#             */
/*   Updated: 2020/02/26 15:37:05 by wanton           ###   ########.fr       */
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
	char			symbol;
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
int					find_slash(char const *str);
char				*get_full_path(char *name, char *path);

/*
**Functions for list t_arg
*/

char				*free_args(t_arg **arg);
void				print_list(t_arg *arg);
t_arg				*ft_create_elem(void);

/*
**Main functions for run commands
*/

int					run_command(char **s_arg, char ***env);
void				proc_signal(int signo);

/*
**Built-in shell commands
*/

int					pwd_script(char **s_arg, char ***env);
int					cd_script(char **s_arg, char ***env);
int					echo_script(char **arg, char ***env);
int					env_script(char **arg, char ***env);
int					setenv_script(char **arg, char ***env);
int					unsetenv_script(char **arg, char ***env);
int					exit_script(char **arg, char ***env);

/*
**Env functions
*/

int					delete_elem(char *elem, char **env);
int					len_env(char **env);
int					find_elem(char *elem, char **env);
int					add_elem(char *name, char *value, char ***env);
char				*take_env_elem(char *name, char **env);
char				*full_env_var(char *name, char **env);
void				print_env(char **env);

/*
**Cd functions
*/

int					change_env_param(char *param, char ***env);

/*
**Scan functions ($ and ~)
*/

int					find_dollar(char *arg);
int					find_not_ascii(int i, char *str);
int					scan_env(char **arg, char **env, int j);
int					scan_tilda(char **arg, char **env, int jno);
char				*get_value(int n, char **env, char *arg, int len);

#endif
