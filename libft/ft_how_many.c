/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_how_many.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 01:34:03 by tlepeche          #+#    #+#             */
/*   Updated: 2015/03/03 21:38:15 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		how_many(char *str, char c)
{
	int	i;
	int result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == c)
			result++;
		i++;
	}
	return (result);
}
