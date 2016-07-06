/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:59:16 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:23:37 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	a;
	unsigned char	*sdst;
	unsigned char	*ssrc;

	sdst = (unsigned char *)dst;
	ssrc = (unsigned char *)src;
	a = 0;
	while (a < n)
	{
		sdst[a] = ssrc[a];
		a++;
	}
	return (dst);
}
