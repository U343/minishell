/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanton <wanton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:40:18 by wanton            #+#    #+#             */
/*   Updated: 2020/02/26 15:18:33 by wanton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		words(char const *s, char c, char c2)
{
	int i;
	int	word;

	i = 0;
	word = 0;
	while ((s[i] == c || s[i] == c2) && s[i])
	{
		i++;
	}
	if (s[i])
		word++;
	while (s[++i])
	{
		if ((s[i] != c || s[i] != c2) && (s[i - 1] == c || s[i - 1] == c2))
			word++;
	}
	return (word);
}

static	int		let(char const *s, char c, int i)
{
	int let;

	let = 0;
	while (s[i] && s[i] != c && s[i] != '\t')
	{
		i++;
		let++;
	}
	return (let);
}

static	void	clear_mass(char **mass, size_t m_i)
{
	size_t	i;

	i = 0;
	while (i < m_i)
	{
		free(mass[i++]);
	}
	free(mass);
}

static	int		mass_filler(char **m, const char *s, char c, size_t i)
{
	size_t	m_i;
	size_t	m_j;

	m_i = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != '\t')
		{
			m_j = 0;
			if (!(m[m_i] = (char *)malloc(sizeof(char) * (let(s, c, i) + 1))))
			{
				clear_mass(m, m_i);
				return (0);
			}
			while (s[i] && s[i] != ' ' && s[i] != '\t')
			{
				m[m_i][m_j++] = s[i++];
			}
			m[m_i++][m_j] = '\0';
		}
		else
			i++;
	}
	m[m_i] = NULL;
	return (1);
}

char			**ft_split_shell(char const *s)
{
	char	**mass;
	size_t	i;

	i = 0;
	if (s)
	{
		if (!(mass = (char **)malloc(sizeof(char *) * (words(s, ' ', '\t') + 1))))
			return ((char **)NULL);
		if (mass_filler(mass, s, ' ', i) == 0)
			return ((char **)NULL);
		return (mass);
	}
	return ((char **)NULL);
}
