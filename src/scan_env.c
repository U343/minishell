/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:22:06 by wanton            #+#    #+#             */
/*   Updated: 2020/02/12 13:30:34 by wanton           ###   ########.fr       */
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
		while (env[j][i - 1] != '=')
		{
			if (s[i] == '\0' || s[i] != env[j][i - 1])
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
**Function gets the value out of the env with name arg
** len - len of the name in arg
** name - part of a arg which overlapping with env
**       Returned: name if successful or NULL if error with allocated memory
*/

static char	*get_value(char **env, char *arg, int len)
{
	int		i;
	char	*name;
	char	*res;

	i = 0;
	if (!(name = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		name[i] = arg[i + 1];
		i++;
	}
	name[i] = '\0';
	if (!(res = take_env_elem(name, env)))
	{
		free(name);
		return (NULL);
	}
	free(name);
	return (res);
}

/*
**Function created new arg with env value
** count - len of the str which overlapping with env variable
** res - value of the env variable
**       Returned: arg if successful or NULL if error with allocated memory
*/

static char	*create_new_arg(int count, char *arg, char *res)
{
	int		len;
	int		flag;
	char	*tmp;

	flag = 0;
	len = ft_strlen(res);
	if (arg[count])
	{
		len += (int)ft_strlen(arg) - count;
		flag = 0;
		while (flag++ <= count)
			arg++;
	}
	if (!(tmp = ft_strnew(len + 1)))
		return (NULL);
	tmp = ft_strcpy(tmp, res);
	if (flag > 0)
		tmp = ft_strcat(tmp, --arg);
	return (tmp);
}

/*
**Function change arg list, arg[j] to be replace on env value or empty line
**       0 is returned if successful
**       -1 is returned if an error with allocated memory
*/

static int	change_arg(char **env, int index, char **arg, int j)
{
	char	*res;
	char	*tmp;

	if (!(res = get_value(env, arg[j], index - 1)))
		return (-1);
	tmp = arg[j];
	if (!(arg[j] = create_new_arg(index, arg[j], res)))
	{
		free(tmp);
		free(res);
		return (-1);
	}
	free(tmp);
	free(res);
	return (0);
}

/*
**Function to replace $NAME with env variable value
**       0 is returned if successful
**       -1 is returned if an error with allocated memory
*/

int			scan_env(char **arg, char **env)
{
	int		j;
	int		index;
	char	*tmp;

	j = -1;
	while (arg[++j])
	{
		if (arg[j][0] == '$')
		{
			if ((index = check_overlap(arg[j], env)) != 0)
			{
				if (change_arg(env, index, arg, j) == -1)
					return (-1);
			}
			else
			{
				tmp = arg[j--];
				index = j;
				while (arg[++index])
					arg[index] = arg[index + 1];
				free(tmp);
			}
		}
	}
	return (0);
}
