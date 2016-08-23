/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 02:46:22 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/22 17:35:56 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			find_object(char *s)
{
	if (!ft_strcmp(s, "sphere:"))
		return (SPHERE);
	if (!ft_strcmp(s, "cylinder:"))
		return (CYLINDER);
	if (!ft_strcmp(s, "plane:"))
		return (PLANE);
	if (!ft_strcmp(s, "cone:"))
		return (CONE);
	if (!ft_strcmp(s, "elips:"))
		return (ELIPS);
	if (!ft_strcmp(s, "triangle:"))
		return (TRIAN);
	if (!ft_strcmp(s, "parallelo:"))
		return (PARA);

	return (NONE);
}

int			find_type(char *s)
{
	if (!s)
		return (NONE);
	if (!ft_strcmp(s, "scene:"))
		return (SCENE);
	if (!ft_strcmp(s, "light:"))
		return (LIGHT);
	if (!ft_strcmp(s, "objects:"))
		return (OBJECT);
	if (!ft_strcmp(s, "camera:"))
		return (CAMERA);
	if (!ft_strcmp(s, "diffuse:"))
		return (DIFFUSE);
	if (!ft_strcmp(s, "parallel:"))
		return (PARALLEL);
	if (!ft_strcmp(s, "direct:"))
		return (DIRECT);
	return (find_object(s));
}

char		*find_scop(char *s, int ref_level)
{
	static int	level;
	char		*ret;
	int			i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '{')
			level++;
		else if (s[i] == '}')
		{
			level--;
			if (level == ref_level)
				break ;
		}
	}
	ret = ft_strsub(s, 0, i + 1);
	return (ret);
}

int			arr_len(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		i++;
	}
	return (i);
}

char		**cpy_carray(char **array)
{
	char	**new;
	int		i;

	i = arr_len(array);
	if (!(new = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (array[++i])
	{
		if (!(new[i] = ft_epur_str_c(array[i], '}')))
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}
