/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 20:19:46 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/12 07:09:59 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmpre(const char *s1, const char *s2, size_t n, unsigned int a)
{
	unsigned int	b;
	int				start;

	b = 0;
	start = -1;
	while (s1[a] == s2[b] && s1[a] != '\0' && a < n)
	{
		a++;
		b++;
		if (s2[b] == '\0')
			start = a - b;
	}
	return (start);
}

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	a;
	char			*sfinal;
	int				start;

	a = 0;
	if (n < (unsigned int)ft_strlen(s2))
		return (NULL);
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[a] != '\0' && a < n)
	{
		if (s1[a] == s2[0])
		{
			start = cmpre(s1, s2, n, a);
			if (start != -1)
			{
				sfinal = (char *)&s1[start];
				return (sfinal);
			}
		}
		a++;
	}
	sfinal = NULL;
	return (sfinal);
}
