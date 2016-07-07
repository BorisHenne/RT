/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 01:39:37 by tlepeche          #+#    #+#             */
/*   Updated: 2015/01/25 05:26:53 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, int i)
{
	int		a;
	int		j;
	char	conv;
	char	*s2;

	if (!s || i < 0)
		return (NULL);
	conv = (char)c;
	a = 0;
	j = 0;
	s2 = ft_strdup(s);
	while (s2[a])
	{
		if (s2[a] == conv)
			j++;
		if (j == i)
		{
			s2[a + 1] = '\0';
			break ;
		}
		a++;
	}
	return (s2);
}
