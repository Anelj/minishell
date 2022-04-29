/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:08:41 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 16:53:37 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_max_size(void)
{
	size_t	max_size;
	size_t	bits;

	max_size = 1;
	bits = sizeof(size_t) * 8;
	while (bits--)
	{
		max_size = max_size * 2;
	}
	return (max_size - 1);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	max_size;
	size_t	len;
	size_t	len1;
	size_t	len2;	
	char	*s;

	max_size = ft_max_size();
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((len1 != max_size) && ((max_size - len1 - 1) >= len2))
		len = len1 + len2;
	else
		return (NULL);
	s = (char *)malloc(len + 1);
	if (s == NULL)
		return (NULL);
	ft_memcpy((void *)s, (const void *)s1, len1);
	ft_memcpy((void *)(s + len1), (const void *)s2, len2 + 1);
	return (s);
}
