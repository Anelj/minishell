/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:20:19 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:35:21 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_destbeforesrc(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	l;

	l = 0;
	while (l < n)
	{
		d[l] = s[l];
		l++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				l;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d > s)
	{
		l = n;
		while (--l)
			d[l] = s[l];
		d[l] = s[l];
	}
	else if (d < s)
	{
		ft_destbeforesrc(d, s, n);
	}
	return (dest);
}
