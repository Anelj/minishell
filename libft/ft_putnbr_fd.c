/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:21:47 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:21:52 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putminus(int nb, int fd)
{
	if (nb < 0)
		ft_putchar('-', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	s[10];
	int		i;

	i = 0;
	if (n == 0)
	{
		ft_putchar('0', fd);
		return ;
	}
	ft_putminus(n, fd);
	while (n != 0)
	{
		if (n % 10 < 0)
			s[i] = -(n % 10) + 48;
		else
			s[i] = n % 10 + 48;
		n = n / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		ft_putchar(*(s + i), fd);
		i--;
	}
}
