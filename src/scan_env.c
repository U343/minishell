/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:22:06 by wanton            #+#    #+#             */
/*   Updated: 2020/02/20 13:26:16 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function for find arg in env
**       Returned: index at the end of an arg (*s)
*/

static int	check_overlap(char *s, char **env, int num)
{
	int j;
	int i;
	int n;
	int flag;

	j = 0;
	while (env[j])
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

static char	*get_value(int n, char **env, char *arg, int len)
{
	int		i;
	char	*name;
	char	*res;

	i = 0;
	if (!(name = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
		name[i++] = arg[n++];
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

static int	change_arg(char **env,int i_start, int i_end, char **arg)
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
**Function to replace $NAME with env variable value
**       0 is returned, if successful
**       -1 is returned, if an error with allocated memory
*/

int 		find_not_ascii(int i, char *str)
{
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	invalid_elem(char **arg, int j, char *str, int n)
{
	int	i_end;

	if ((i_end = find_not_ascii(n, str)) == -1 && n == 1)
	{
		ft_putstr("ok2\n");
		while (arg[++j])
			arg[j] = arg[j + 1];
		return (0);
	}
	if ((*arg = create_new_arg(n, i_end, *arg, "")) == NULL)
		return (-1);
	return (0);
}

int 		find_dollar(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i++] == '$')
			return (i);
	}
	return (-1);
}

int			scan_env(char **arg, char **env)
{
	int		j;
	int		i_start;
	int 	i_end;
	char	*tmp;

	j = -1;
	while (arg[++j])
	{
		if ((i_start = find_dollar(arg[j])) != -1)
		{
			/*ft_putnbr(i_start);
			ft_putchar('\n');*/
			if ((i_end = check_overlap(arg[j], env, i_start)) != 0)
			{
				/*ft_putnbr(i_end);
				ft_putchar('\n');*/
				if (change_arg(env, i_start, i_end, &arg[j]) == -1)
					return (-1);
			}
			else
			{
				ft_putstr("ok\n");
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
