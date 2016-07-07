/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 21:37:58 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:27:16 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int a;

	a = 0;
	if (!s1 || !s2)
		return (0);
	while (a <= ft_strlen(s1) && a <= ft_strlen(s2) && a < n)
	{
		if (s1[a] != s2[a])
			return (0);
		a++;
	}
	return (1);
}
