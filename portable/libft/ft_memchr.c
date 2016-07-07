/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 18:16:10 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/09 05:41:29 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	conv;
	unsigned int	a;

	str = (unsigned char *)s;
	conv = (unsigned char)c;
	a = 0;
	while (a < n)
	{
		if (str[a] == conv)
			return ((void *)(str + a));
		a++;
	}
	return (NULL);
}
