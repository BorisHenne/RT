/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:31:40 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/12 01:09:08 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_vec		init_vector(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double		get_length(t_vec vec)
{
	double	x;
	double	y;
	double	z;

	x = pow(vec.x, 2);
	y = pow(vec.y, 2);
	z = pow(vec.z, 2);
	return (sqrt(x + y + z));
}

t_vec		normalize(t_vec vec)
{
	t_vec	res;
	double	len;

	len = get_length(vec);
	if (len == 0.0f)
	{
		len = 1; //!\ HELP !!!
	}
	res.x = vec.x / len;
	res.y = vec.y / len;
	res.z = vec.z / len;
	return (res);
}

