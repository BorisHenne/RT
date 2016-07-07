/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:26:44 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:18:52 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned int	a;
	int				result;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	a = 0;
	while (a < size)
	{
		if (str1[a] != str2[a])
		{
			result = str1[a] - str2[a];
			return (result);
		}
		a++;
	}
	return (0);
}
