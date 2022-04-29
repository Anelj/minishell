/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:13:35 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 16:26:42 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

char	*ft_strdup(const char *src)
{
	int		l;
	int		i;
	char	*dest;

	l = 0;
	while (src[l])
		l++;
	dest = malloc(l + 1);
	if (dest == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (i <= l)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
