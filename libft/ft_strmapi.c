/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:04:17 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:05:51 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ar;
	unsigned int	i;
	unsigned int	length;

	length = (unsigned int)ft_strlen(s);
	ar = (char *)malloc((length + 1) * sizeof(char));
	if (ar == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		ar[i] = (*f)(i, s[i]);
		i++;
	}
	ar[i] = '\0';
	return (ar);
}
