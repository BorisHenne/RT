/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 16:44:46 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/22 16:46:00 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

float		get_num(char **values)
{
	return (ft_atof(values[0]));
}

int			get_bool(char **values)
{
	if (!ft_strcmp(values[0], "y"))
		return (1);
	else if (!ft_strcmp(values[0], "n"))
		return (0);
	return (-1);
}

int			get_enum(char **values)
{
	if (!strcmp(values[0], "marble"))
		return (MARBLE);
	else if (!strcmp(values[0], "checker"))
		return (CHECKER);
	else if (!strcmp(values[0], "none"))
		return (NONE);
	else if (!strcmp(values[0], "sepia"))
		return (SEPIA);
	else if (!strcmp(values[0], "bn"))
		return (NOIR_BLANC);
	return (-1);
}

t_vec		*get_vec(char **values, char *name)
{
	t_vec	*vec;
	int		n_values;

	if ((n_values = arr_len(values)) != 3)
	{
		ft_putstr(n_values < 3 ? "missing value in '" : "too many values in '");
		ft_putstr(name);
		ft_putendl("'");
		return (NULL);
	}
	if (!is_number(values[0]) || !is_number(values[1]) || !is_number(values[2]))
	{
		ft_putstr("value != number in '");
		ft_putstr(name);
		ft_putendl("'");
		return (NULL);
	}
	if (!(vec = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	vec->x = ft_atof(values[0]);
	vec->y = ft_atof(values[1]);
	vec->z = ft_atof(values[2]);
	return (vec);
}

t_quad		*get_quad(char **values)
{
	t_quad	*quad;
	int		n_values;

	if ((n_values = arr_len(values)) != 3)
	{
		if (n_values < 3)
			ft_putendl("missing value in 'quad'");
		else
			ft_putendl("too many values in 'quad'");
		return (NULL);
	}
	if (!is_number(values[0]) || !is_number(values[1]) || !is_number(values[2]))
	{
		ft_putstr("value != number in 'quad'");
		return (NULL);
	}
	if (!(quad = (t_quad *)malloc(sizeof(t_quad))))
		return (NULL);
	quad->A = ft_atof(values[0]);
	quad->B = ft_atof(values[1]);
	quad->C = ft_atof(values[2]);
	return (quad);
}
