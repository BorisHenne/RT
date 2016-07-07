/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:59:16 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:24:26 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char *src, size_t n)
{
	unsigned int	a;

	a = 0;
	while (a < n && src[a] != '\0')
	{
		dst[a] = src[a];
		a++;
	}
	if (ft_strlen(src) < n)
	{
		while (dst[a] != '\0')
		{
			dst[a] = '\0';
			a++;
		}
	}
	return (dst);
}
