/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 21:38:15 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:26:09 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	a = 0;
	b = 0;
	while (s1[a] != '\0')
	{
		str[b] = s1[a];
		a++;
		b++;
	}
	a = 0;
	while (s2[a] != '\0')
	{
		str[b] = s2[a];
		a++;
		b++;
	}
	str[b] = '\0';
	return (str);
}
