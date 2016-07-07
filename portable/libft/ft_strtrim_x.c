/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 21:51:51 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/12 07:11:39 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*cat_end(char *str, char x)
{
	int		a;

	a = ft_strlen(str) - 1;
	while (str[a] == x)
	{
		str[a] = '\0';
		a--;
	}
	return (str);
}

char		*ft_strtrim_x(char const *s, char x)
{
	char	*str1;
	char	*str2;
	int		a;
	int		b;

	str1 = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	a = 0;
	b = 0;
	while (s[a] == x)
		a++;
	while (s[a] != '\0')
	{
		str1[b] = s[a];
		a++;
		b++;
	}
	str1[b] = '\0';
	str1 = cat_end(str1, x);
	str2 = (char *)malloc(sizeof(char) * (ft_strlen(str1) + 1));
	str2 = ft_strcpy(str2, str1);
	return (str2);
}
