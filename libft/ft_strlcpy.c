/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:07:00 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:07:25 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	l;

	l = 0;
	if (n == 0)
		return (ft_strlen(src));
	while (l < n - 1 && src[l])
	{
		dst[l] = src[l];
		l++;
	}
	dst[l] = '\0';
	return (ft_strlen(src));
}
