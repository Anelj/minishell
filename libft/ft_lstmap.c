/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:45:22 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 16:27:15 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnextnullmalloc(t_list *rlst, void (*del)(void *))
{
	ft_lstclear(&rlst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*rlst;
	t_list	*rlst1;

	tmp = lst;
	rlst = NULL;
	while (tmp)
	{
		if (rlst == NULL)
		{
			rlst1 = ft_lstnew((*f)(tmp->content));
			if (rlst1 == NULL)
				return (rlst);
			rlst = rlst1;
		}
		else
		{
			rlst1->next = ft_lstnew((*f)(tmp->content));
			if (rlst1->next == NULL)
				return (ft_lstnextnullmalloc(rlst, del));
			rlst1 = rlst1->next;
		}
		tmp = (tmp)->next;
	}
	return (rlst);
}
