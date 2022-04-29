/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:26:36 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:27:19 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *v, int i, size_t n)
{
	const unsigned char	*s;
	unsigned char		c;

	s = (const unsigned char *)v;
	c = (unsigned char)i;
	if (n == 0)
		return (NULL);
	while (*s && *s != c && --n)
	{
		s++;
	}
	if (*s == c)
		return ((void *)s);
	return (NULL);
}
