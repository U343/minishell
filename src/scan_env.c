/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:22:06 by wanton            #+#    #+#             */
/*   Updated: 2020/02/26 12:19:11 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function for find arg in env
**       Returned: index at the end of an arg (*s)
*/

static int	check_overlap(char *s, char **env, int num)
{
	int		j;
	int		i;
	int		n;
	int		flag;

	j = -1;
	while (env[++j])
	{
		i = 0;
		n = num;
		flag = 1;
		while (env[j][i] != '=')
		{
			if (s[n] == '\0' || s[n] != env[j][i])
			{
				flag = 0;
				break ;
			}
			n++;
			i++;
		}
		if (flag == 1 && !ft_isalpha(s[n]) && !ft_isdigit(s[n]))
			return (n);
	}
	return (0);
}

/*
**Function created new arg with env value
** n - start index of the str which overlapping with env variable
**      (n + 1) because, n - symbol's index after $
** count - len of the str which overlapping with env variable
** res - value of the env variable
**       Returned: arg if successful or NULL if error with allocated memory
*/

static char	*create_new_arg(int n, int count, char *arg, char *res)
{
	int		len;
	int		flag;
	char	*tmp;
	char	*foo;

	flag = 0;
	foo = arg;
	len = (int)ft_strlen(res) + (n - 1);
	if (arg[count])
	{
		len += (int)ft_strlen(arg) - count;
		while (flag++ <= count)
			foo++;
	}
	if (!(tmp = ft_strnew(len + 1)))
		return (NULL);
	tmp = ft_strncpy(tmp, arg, n - 1);
	tmp = ft_strcat(tmp, res);
	if (flag > 0)
		tmp = ft_strcat(tmp, --foo);
	return (tmp);
}

/*
**Function change arg list, arg[j] to be replace on env value or empty line
**       0 is returned, if successful
**       -1 is returned, if an error with allocated memory
*/

static int	change_arg(char **env, int i_start, int i_end, char **arg)
{
	char	*res;
	char	*tmp;

	if (!(res = get_value(i_start, env, *arg, i_end - i_start)))
		return (-1);
	tmp = *arg;
	if (!(*arg = create_new_arg(i_start, i_end, *arg, res)))
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
**Function delete invalid env name (delete symbol $ and symbols after $)
** str - argument which need change
** j - index of arg, before str (j always 1 or more)
** n - index of symbol after $ (start of the env variable)
**       	0 is returned,  if successful
**          -1 is returned, if error in create_new_arg()
*/

static int	invalid_elem(char **arg, int j, char *str, int n)
{
	int	i_end;

	if ((i_end = find_not_ascii(n, str)) == -1 && n == 1)
	{
		while (arg[++j])
			arg[j] = arg[j + 1];
		return (0);
	}
	if ((arg[j + 1] = create_new_arg(n, i_end, str, "")) == NULL)
		return (-1);
	return (0);
}

/*
**Function checks arg for availability on env variables
** j - index for arg
**       0 is returned, if successful
**       -1 is returned, if error
*/

int			scan_env(char **arg, char **env, int j)
{
	int		i_start;
	int		i_end;
	char	*tmp;

	j = -1;
	while (arg[++j])
	{
		if ((i_start = find_dollar(arg[j])) != -1)
		{
			if ((i_end = check_overlap(arg[j], env, i_start)) != 0)
			{
				if (change_arg(env, i_start, i_end, &arg[j]) == -1)
					return (-1);
			}
			else
			{
				tmp = arg[j];
				if (invalid_elem(arg, j - 1, tmp, i_start) == -1)
					return (-1);
				free(tmp);
			}
			j = j - 1;
		}
	}
	return (0);
}
