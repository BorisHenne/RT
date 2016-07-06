/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:55:23 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:29:11 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		a;
	char	conv;
	char	*s2;

	conv = (char)c;
	a = ft_strlen(s);
	s2 = (char *)s;
	while (a >= 0)
	{
		if (s[a] == conv)
			return (s2 + a);
		a--;
	}
	return (NULL);
}
