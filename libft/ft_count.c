/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 03:23:39 by tlepeche          #+#    #+#             */
/*   Updated: 2014/12/02 03:27:58 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char *str, char c)
{
	int i;
	int result;

	if (!str)
		return (0);
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
