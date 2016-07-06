/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrevchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 03:20:11 by tlepeche          #+#    #+#             */
/*   Updated: 2015/01/14 17:39:08 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrevchr(const char *s, int c)
{
	int		i;
	char	conv;
	char	*s2;

	if (!s)
		return (NULL);
	conv = (char)c;
	i = ft_strlen(s);
	while (s[i] != conv)
		i--;
	s2 = ft_strsub(s, 0, i);
	return (s2);
}
