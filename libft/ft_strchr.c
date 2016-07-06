/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:55:23 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:20:59 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	a;
	char			conv;
	char			*s2;

	conv = (char)c;
	a = 0;
	while (a <= ft_strlen(s))
	{
		if (s[a] == conv)
		{
			s2 = (char *)&s[a];
			return (s2);
		}
		a++;
	}
	return (NULL);
}
