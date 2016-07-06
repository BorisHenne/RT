/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 22:16:10 by tlepeche          #+#    #+#             */
/*   Updated: 2015/03/22 02:42:48 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		height(char const *s, char c)
{
	int		count;
	int		a;

	count = 0;
	a = 0;
	while (s[a] != '\0')
	{
		if (s[a] != c && (s[a + 1] == c || s[a + 1] == '\0'))
			count++;
		a++;
	}
	return (count);
}

static int		lenght(const char *s, int a, int len, char c)
{
	while (s[a] != c && s[a] != '\0')
	{
		len++;
		a++;
	}
	return (len);
}

static char		*prt(char const *s, char c, int a, char *str)
{
	int b;

	b = 0;
	while (s[a] != c && s[a] != '\0')
	{
		str[b] = s[a];
		a++;
		b++;
	}
	str[b] = '\0';
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char			**tab;
	unsigned int	a;
	int				x;
	int				y;

	a = 0;
	x = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (height(s, c) + 1));
	while (s[a] != '\0' && a < ft_strlen(s))
	{
		y = 0;
		if (s[a] != c)
		{
			y = lenght(s, a, y, c);
			tab[x] = (char *)malloc(sizeof(char) * (y + 1));
			tab[x] = prt(s, c, a, tab[x]);
			a = a + y - 1;
			x++;
		}
		a++;
	}
	tab[x] = NULL;
	return (tab);
}
