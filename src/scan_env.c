/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:22:06 by wanton            #+#    #+#             */
/*   Updated: 2020/02/11 15:42:29 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function for find arg in env
**       Returned: index at the end of an arg (*s)
*/

static int	check_overlap(char *s, char **env)
{
	int j;
	int i;
	int flag;

	j = 0;
	while (env[j])
	{
		i = 1;
		flag = 1;
		while (s[i] && env[j][i - 1] != '=')
		{
			if (s[i] != env[j][i - 1])
			{
				flag = 0;
				break ;
			}
			i++;
		}
		if (flag == 1 && !ft_isalpha(s[i]) && !ft_isdigit(s[i]))
			return (i);
		j++;
	}
	return (0);
}

/*
**Function gets the name out of the arg
** len - len of the name in arg
**       Returned: name if successful or NULL if error with allocated memory
*/

static char *get_name(char *arg, int len)
{
	int 	i;
	char	*name;

	i = 1;
	if (!(name = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		name[i] = arg[i + 1];
		i++;
	}
	name[i] = '\0';
	return (name);
}

/*
**Function created new arg with env value
** count - len of the str which overlaping with env variable
** res - value of the env variable
**       Returned: arg if successful or NULL if error with allocated memory
*/

static char	*create_new_arg(int count, char *arg, char *res)
{
	int 	len;
	int 	flag;
	char 	*tmp;

	flag = 0;
	len = ft_strlen(res);
	if (arg[count])
	{
		if (!ft_isdigit(arg[count]) && !ft_isalpha(arg[count]))
		{
			len += (int)ft_strlen(arg) - count;
			flag = 0;
			while (flag++ <= count)
				arg++;
		}
	}
	if (!(tmp = ft_strnew(len + 1)))
		return (NULL);
	tmp = ft_strcpy(tmp, res);
	if (flag > 0)
		tmp = ft_strcat(tmp, arg);
	return (tmp);
}

/*
**Function to replace $NAME with env variable value
**       0 is returned if successful
**       -1 is returned if an error with allocated memory
*/

int 	scan_env(char **arg, char **env)
{
	int 	j;
	int 	index;
	char 	*res;
	char 	*tmp;
	char 	*name;


	j = 0;
	while (arg[j])
	{
		if (arg[j][0] == '$')
		{
			if ((index = check_overlap(arg[j], env)) != 0)
			{
				if (!(name = get_name(arg[j], index - 1)))
					return (-1);
				if (!(res = take_env_elem(name, env)))
					return (-1);
				tmp = arg[j];
				arg[j] = create_new_arg(index, arg[j], res);
				/*free(tmp);
				free(name);
				free(res);*/
			}
		}
		j++;
	}
	return (0);
}
