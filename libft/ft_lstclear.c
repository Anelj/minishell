/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:24:05 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:24:25 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **begin_list, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp1;

	tmp = *begin_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		ft_lstdelone(tmp1, del);
	}
	*begin_list = NULL;
}
