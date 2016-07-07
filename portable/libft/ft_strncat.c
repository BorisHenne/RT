/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:41:20 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:26:55 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;

	a = 0;
	b = ft_strlen(s2);
	c = ft_strlen(s1);
	while (a <= b && a < n)
	{
		s1[c + a] = s2[a];
		a++;
	}
	s1[c + a] = '\0';
	return (s1);
}
