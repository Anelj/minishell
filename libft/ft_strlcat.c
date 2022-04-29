/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:07:58 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:13:10 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*d;
	size_t	i;
	size_t	s;

	i = 1;
	d = dest;
	s = size;
	if (size == 0)
		return (ft_strlen(src));
	while (*d && --s)
	{
		d++;
		i++;
	}
	if ((*d))
		return (size + ft_strlen(src));
	while (size != i && *src != '\0')
	{
		*d++ = *src++;
		i++;
	}
	*d = '\0';
	return (ft_strlen(dest) + ft_strlen(src));
}
