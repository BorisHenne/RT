/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 01:42:57 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/23 05:53:44 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_elem;
	void	*temp;

	new_elem = (t_list *)malloc(sizeof(t_list));
	temp = (void *)ft_memalloc(content_size);
	new_elem->content = ft_memalloc(content_size);
	if (!temp || !new_elem)
		return (NULL);
	if (!content || !content_size)
	{
		new_elem->content = NULL;
		new_elem->content_size = 0;
	}
	else
	{
		temp = ft_memcpy(temp, content, content_size);
		new_elem->content = ft_memcpy(new_elem->content, content, content_size);
		new_elem->content_size = content_size;
	}
	new_elem->next = NULL;
	free(temp);
	return (new_elem);
}
