/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_blank.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 21:38:23 by tlepeche          #+#    #+#             */
/*   Updated: 2015/03/03 21:38:25 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		height(char const *s)
{
	int		count;
	int		a;

	count = 0;
	a = 0;
	while (s[a] != '\0')
	{
		if (ft_isspace(s[a]) == 0 &&
				(ft_isspace(s[a + 1]) == 1 || s[a + 1] == '\0'))
			count++;
		a++;
	}
	return (count);
}

static int		lenght(const char *s, int a, int len)
{
	while (ft_isspace(s[a]) == 0 && s[a] != '\0')
	{
		len++;
		a++;
	}
	return (len);
}

static char		*prt(char const *s, int a, char *str)
{
	int b;

	b = 0;
	while (ft_isspace(s[a]) == 0 && s[a] != '\0')
	{
		str[b] = s[a];
		a++;
		b++;
	}
	str[b] = '\0';
	return (str);
}

char			**ft_strsplit_blank(char const *s)
{
	char			**tab;
	unsigned int	a;
	int				x;
	int				y;

	a = 0;
	x = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (height(s) + 1));
	while (s[a] != '\0' && a < ft_strlen(s))
	{
		y = 0;
		if (ft_isspace(s[a]) == 0)
		{
			y = lenght(s, a, y);
			tab[x] = (char *)malloc(sizeof(char) * (y + 1));
			tab[x] = prt(s, a, tab[x]);
			a = a + y - 1;
			x++;
		}
		a++;
	}
	tab[x] = NULL;
	return (tab);
}
