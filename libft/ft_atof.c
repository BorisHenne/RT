/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:54:54 by tlepeche          #+#    #+#             */
/*   Updated: 2016/08/09 01:58:03 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	space(char *str)
{
	int a;

	a = 0;
	while (str[a] != '\0')
	{
		if (ft_isspace(str[a]) == 1)
			a++;
		else
			return (a);
	}
	return (a);
}

static int	convert_result(char *str, int a, int *precision)
{
	int		b;
	int		result;

	b = 0;
	result = 0;
	while (ft_isdigit(str[a]) == 1 || str[a] == '.')
	{
		if (str[a] == '.')
			b += 1;
		else
		{
			result = result * 10 + (str[a] - 48);
			if (b == 1)
				*precision *= 10;
		}
		a++;
	}
	return (result);
}

#include <stdio.h>
float		ft_atof(char *str)
{
	int		a;
	int		result;
	int		neg;
	int		precision;

	result = 0;
	neg = 1;
	a = space(str);
	if (str == NULL)
		return (0);
	if (str[a] == '-' && ft_isdigit(str[a + 1]) == 1)
	{
		neg = -1;
		a++;
	}
	if (str[a] == '+' && ft_isdigit(str[a + 1]) == 1)
		a++;
	precision = 1;
	result = convert_result(str, a, &precision);
	result = result * neg;
	return ((float)result / precision);
}
