/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 01:01:05 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/12 07:12:26 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*print(char *str, unsigned int n, int a)
{
	if (n >= 10)
	{
		str = print(str, n / 10, a - 1);
		str = print(str, n % 10, a);
	}
	else
	{
		str[a] = (n + 48);
	}
	return (str);
}

static int		poscount(int num, int count)
{
	while (num >= 10)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static int		negcount(int num, int count)
{
	count++;
	while (num <= -10)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	int				count;
	int				a;
	char			*str;
	unsigned int	num;

	a = 0;
	count = 1;
	if (n >= 0)
		count = poscount(n, count);
	else
		count = negcount(n, count);
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (n < 0)
	{
		str[a] = '-';
		num = n * -1;
		a++;
	}
	else
		num = n;
	str = print(str, num, count - 1);
	str[count] = '\0';
	return (str);
}
