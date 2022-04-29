/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:55:01 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 13:55:24 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_istotrim(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*s;

	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(s1));
	i = len - 1;
	while (i != 0 && ft_istotrim(s1[i], set))
		i--;
	if (i == 0 && ft_istotrim(s1[i], set))
		return (ft_strdup(""));
	len = i + 1;
	while (*s1 && ft_istotrim(*s1, set))
	{
		len--;
		s1++;
	}
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	s[len] = '\0';
	return ((char *)ft_memcpy((void *)s, (const void *)s1, len));
}
