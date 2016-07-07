/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:41:20 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:23:59 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		a;

	a = 0;
	if (!s1)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	while (s1[a] != '\0')
	{
		s2[a] = s1[a];
		a++;
	}
	s2[a] = '\0';
	return (s2);
}
