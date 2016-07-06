/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 18:56:30 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/10 04:22:53 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char c;

	if (len != 0)
	{
		c = *(char *)src;
		ft_memmove(dst + 1, src + 1, len - 1);
		*(char *)dst = c;
	}
	return (dst);
}
