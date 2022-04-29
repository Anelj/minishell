/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:57:08 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 13:57:13 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	b;
	size_t	to_find_len;

	i = 0;
	to_find_len = ft_strlen(to_find);
	if (to_find_len == 0)
		return ((char *)str);
	while (str[i] != '\0' && len >= to_find_len)
	{
		b = i;
		j = 0;
		while (to_find[j] == str[b] && str[b] != '\0')
		{
			j++;
			b++;
		}
		if (to_find[j] == '\0')
			return ((char *)(str + i));
		len--;
		i++;
	}
	return (NULL);
}
