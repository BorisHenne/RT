/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 20:19:46 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/12 07:13:01 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	compare(const char *s1, const char *s2, int a)
{
	int b;
	int start;

	b = 0;
	start = -1;
	while (s1[a] == s2[b] && s1[a] != '\0')
	{
		a++;
		b++;
		if (s2[b] == '\0')
			start = a - b;
	}
	return (start);
}

char		*ft_strstr(const char *s1, const char *s2)
{
	int		a;
	char	*sfinal;
	int		start;

	a = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[a] != '\0')
	{
		if (s1[a] == s2[0])
		{
			start = compare(s1, s2, a);
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
