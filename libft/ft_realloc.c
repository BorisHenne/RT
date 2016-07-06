/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 07:34:57 by tlepeche          #+#    #+#             */
/*   Updated: 2015/02/26 02:56:09 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*p_ptr;

	if (!ptr)
		return (ft_memalloc(size));
	if (!size)
		return (ptr);
	if (!(p_ptr = ft_memalloc(size)))
		return (ptr);
	p_ptr = ft_memcpy(p_ptr, ptr, ft_strlen(ptr));
	free(ptr);
	ptr = NULL;
	return (p_ptr);
}
