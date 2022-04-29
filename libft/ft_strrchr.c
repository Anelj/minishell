/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:55:58 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 13:56:10 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	f;
	int		flag;

	i = 0;
	f = 0;
	flag = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			f = i;
			flag = 0;
		}
		i++;
	}
	if (flag && s[i] != c)
		return (NULL);
	if (s[i] == c)
		f = i;
	return ((char *)(s + f));
}
