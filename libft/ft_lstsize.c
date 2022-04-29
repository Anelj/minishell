/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:40:02 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:40:07 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *begin_list)
{
	int		l;
	t_list	*tmp;

	tmp = begin_list;
	l = 0;
	while (tmp)
	{
		tmp = tmp->next;
		l++;
	}
	return (l);
}
