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

static int	ft_quotes_helper(int *lw, const char **str, const char *s)
{
	if (*str != s)
		*str = s;
	return (*lw);
}

char	**ft_split_freestrs(char **strs, char **ss)
{
	*strs = NULL;
	strs = ss;
	while (*strs)
		free(*strs++);
	free(ss);
	return (NULL);
}

int	ft_quotes(const char **str, int *lw)
{
	const char	*s;
	char		c;

	s = *str;
	c = ' ';
	if (*s && (*s == 39 || *s == 34))
	{
		c = *s;
		s++;
	}
	while (*s && *s != c)
	{
		(*lw) = *lw + 1;
		s++;
	}
	return (ft_quotes_helper(lw, str, s));
}
