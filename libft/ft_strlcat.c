/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:41:20 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/10 09:47:47 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, char const *s2, size_t size)
{
	unsigned int a;
	unsigned int c;

	a = 0;
	c = ft_strlen(s1);
	if (size < c)
		return (size + ft_strlen(s2));
	while (a < (size - c - 1) && s2[a] != '\0')
	{
		s1[c + a] = s2[a];
		a++;
	}
	s1[c + a] = '\0';
	return (c + ft_strlen(s2));
}
