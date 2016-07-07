/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 08:02:29 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/17 23:03:16 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_endlst(t_list *last)
{
	while (last->next)
		last = last->next;
	return (last);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first_lst;
	t_list	*new_lst;

	first_lst = NULL;
	if (!f || !lst)
		return (NULL);
	while (lst)
	{
		new_lst = (t_list *)malloc(sizeof(t_list));
		if (!new_lst)
			return (NULL);
		new_lst = (*f)(lst);
		if (!first_lst)
		{
			first_lst = new_lst;
			first_lst->next = NULL;
		}
		else
			(ft_endlst(first_lst))->next = new_lst;
		lst = lst->next;
	}
	return (first_lst);
}
