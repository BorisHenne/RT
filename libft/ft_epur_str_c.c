/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 02:19:52 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/09 00:48:20 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			new_len(char *s)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != '\t' && s[i] != ' ')
			len++;
	}
	return (len);
}

char		*ft_epur_str_c(char *s, char c)
{
	int		i;
	int		j;
	char	*new;

	if (!(new = (char *)malloc(sizeof(char) * (new_len(s) + 1))))
		return (NULL);
	i = -1;
	j = -1;
	while (s[++i])
	{
		if (s[i] != c)
		{
			new[++j] = s[i];
		}
	}
	new[j + 1] = '\0';
	s = NULL;
	return (new);
}
