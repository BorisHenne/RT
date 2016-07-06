/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:54:54 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/12 07:01:33 by tlepeche         ###   ########.fr       */
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

int			ft_atoi(char *str)
{
	int a;
	int result;
	int neg;

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
	while (ft_isdigit(str[a]) == 1)
	{
		result = result * 10 + (str[a] - 48);
		a++;
	}
	result = result * neg;
	return (result);
}
