/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:10:07 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 16:58:58 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordlen5(char const *s, char c)
{
	int	l;

	l = 0;
	while (*s && *s != c)
	{
		l++;
		s++;
	}
	return (l);
}

static int	ft_fill5(char **strs, char const **s_tosplit, char c)
{
	int			l;
	int			i;
	char const	*s;

	s = *s_tosplit;
	l = ft_wordlen5(s, c);
	if (l == 0)
		return (0);
	*strs = (char *)malloc(sizeof(char) * (l + 1));
	if (*strs == NULL)
	{
		return (-1);
	}
	(*strs)[l] = '\0';
	i = 0;
	while (l--)
	{
		(*strs)[i] = *s;
		i++;
		s++;
	}
	*s_tosplit = s;
	return (1);
}

static char	**ft_fillstrs5(char **ss, char const *s, char c, int l)
{
	int		i;
	char	**strs;

	strs = ss;
	while (l-- && *s)
	{
		while (*s == c)
			s++;
		i = ft_fill5(strs, &(s), c);
		if (i == 1)
		{
			strs++;
		}
		else if (i == -1)
		{
			*strs = NULL;
			strs = ss;
			while (*strs)
				free(*strs++);
			free(ss);
			return (NULL);
		}
	}
	return (ss);
}

static int	ft_countstrs5(char const *s, char c)
{
	int	l;
	int	lw;

	if (!*s)
		return (0);
	l = 0;
	lw = 0;
	while (*s)
	{
		if (*s == c && lw != 0)
		{
			l++;
			lw = 0;
		}
		else if (*s != c)
			lw++;
		s++;
	}
	if (lw != 0)
		l++;
	return (l);
}

char	**ft_split(char const *s, char c)
{
	int		l;
	char	**strs;

	l = ft_countstrs5(s, c);
	strs = (char **)malloc(8 * (l + 1));
	if (strs == NULL)
		return (NULL);
	strs[l] = NULL;
	return (ft_fillstrs5(strs, s, c, l));
}
