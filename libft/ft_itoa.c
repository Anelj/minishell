/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:41:10 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:41:42 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_revstr(int n, char *s)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		if (n % 10 < 0)
			s[i] = -(n % 10) + 48;
		else
			s[i] = n % 10 + 48;
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_putchar(int i, char *s, char *str, int minus)
{
	str[i + minus] = '\0';
	if (minus)
		*str++ = '-';
	i--;
	while (i >= 0)
	{
		*str = *(s + i);
		str++;
		i--;
	}
}

char	*ft_itoa(int n)
{
	int		minus;
	int		i;
	char	*str;
	char	s[10];

	if (n == 0)
	{
		s[0] = '0';
		i = 1;
	}
	else
		i = ft_revstr(n, s);
	minus = 0;
	if (n < 0)
		minus = 1;
	str = (char *)malloc(i + 1 + minus);
	if (str == NULL)
		return (NULL);
	ft_putchar(i, s, str, minus);
	return (str);
}
