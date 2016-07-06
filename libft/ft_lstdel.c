/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 04:22:27 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:18:12 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (alst == NULL || *alst == NULL || del == NULL)
		return ;
	while ((*alst)->next != NULL)
	{
		(*del)((*alst)->content, (*alst)->content_size);
		*alst = (*alst)->next;
	}
	free(*alst);
	*alst = NULL;
}
