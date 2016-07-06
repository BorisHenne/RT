/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:05:16 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:17:58 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	a;
	unsigned char	*sdst;
	unsigned char	*ssrc;
	unsigned char	conv;

	a = 0;
	sdst = (unsigned char *)dst;
	ssrc = (unsigned char *)src;
	conv = (unsigned char)c;
	while (a < n)
	{
		sdst[a] = ssrc[a];
		if (ssrc[a] == conv)
		{
			return ((void *)&sdst[a + 1]);
		}
		a++;
	}
	return (NULL);
}
