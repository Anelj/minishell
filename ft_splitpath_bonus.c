/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/03 17:17:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wordlen(char const *s, char c)
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

static int	ft_fill(char **strs, char const **s_tosplit, char c)
{
	int			l;
	int			i;
	char const	*s;

	s = *s_tosplit;
	l = ft_wordlen(s, c);
	if (l == 0)
		return (0);
	*strs = (char *)malloc(sizeof(char) * (l + 2));
	if (*strs == NULL)
	{
		return (-1);
	}
	(*strs)[l] = '/';
	(*strs)[l + 1] = '\0';
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

static char	**ft_fillstrs(char **ss, char const *s, char c, int l)
{
	int		i;
	char	**strs;

	strs = ss;
	while (l-- && *s)
	{
		while (*s == c)
			s++;
		i = ft_fill(strs, &(s), c);
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

static int	ft_countstrs(char const *s, char c)
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

char	**ft_splitpath(char const *s, char c)
{
	int		l;
	char	**strs;

	l = ft_countstrs(s, c);
	strs = (char **)malloc(8 * (l + 1));
	if (strs == NULL)
		return (NULL);
	strs[l] = NULL;
	return (ft_fillstrs(strs, s, c, l));
}
