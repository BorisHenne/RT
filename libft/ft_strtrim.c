/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 21:51:51 by tlepeche          #+#    #+#             */
/*   Updated: 2016/08/08 04:28:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*catend(char *str)
{
	int		a;

	a = ft_strlen(str) - 1;
	while (str[a] == ' ' || str[a] == '\n' || str[a] == '\t')
	{
		str[a] = '\0';
		a--;
	}
	return (str);
}

char		*ft_strtrim(char const *s)
{
	char	*str1;
	char	*str2;
	int		a;

	a = 0;
	if (!s)
		return (NULL);
	while (s[a] == ' ' || s[a] == '\t' || s[a] == '\n')
		a++;
	str1 = ft_strsub(s, a, ft_strlen(s));
	str1 = catend(str1);
	str2 = (char *)malloc(sizeof(char) * (ft_strlen(str1) + 1));
	str2 = ft_strcpy(str2, str1);
	free(str1);
	return (str2);
}
