/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:16:50 by tlepeche          #+#    #+#             */
/*   Updated: 2014/11/04 20:45:45 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	conv;
	char	*str;
	int		a;

	conv = (unsigned char)c;
	str = b;
	a = 0;
	while (len != 0)
	{
		str[a] = conv;
		len--;
		a++;
	}
	b = str;
	return (b);
}
