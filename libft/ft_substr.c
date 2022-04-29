/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:53:59 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 16:47:17 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_emptystr(void)
{
	char	*s;

	s = (char *)malloc(sizeof(char));
	if (s == NULL)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*strcp;
	size_t	size;

	size = ft_strlen(s);
	if (start >= size)
		return (ft_emptystr());
	size = size - start;
	if (len < size)
		size = len;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	strcp = str;
	str[size] = '\0';
	if (size == 0)
		return (str);
	while (size--)
	{
		*strcp++ = s[start];
		start++;
	}
	return (str);
}
