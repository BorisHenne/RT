/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 02:18:07 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/13 05:14:15 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
// b - a
t_vec		vec_sub(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = b.x - a.x;
	res.y = b.y - a.y;
	res.z = b.z - a.z;
	return (res);
}

t_vec		vec_add(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec		scalar_product(t_vec a, double b)
{
	t_vec	res;

	res.x = a.x * b;
	res.y = a.y * b;
	res.z = a.z * b;
	return (res);
}

t_vec		cross_product(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = (a.y * b.z) - (a.z * b.y);
	res.y = (a.z * b.x) - (a.x * b.z);
	res.z = (a.x * b.y) - (a.y * b.x);
	return (res);
}

double		dot_product(t_vec a, t_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec	vec_rot_y(t_vec a, double angle)
{
	t_vec res;

	res.x = a.z * sin(angle) + a.x * cos(angle);
	res.y = a.y;
	res.z = a.z * cos(angle) - a.x * sin(angle);
	return (res);
}

t_vec	vec_rot_x(t_vec a, double angle)
{
	t_vec res;

	res.x = a.x;
	res.y = a.y * cos(angle) - a.z * sin(angle);
	res.z = a.y * sin(angle) + a.z * cos(angle);
	return (res);
}

t_vec	vec_rot_z(t_vec a, double angle)
{
	t_vec res;

	res.x = a.x * cos(angle) - a.y * sin(angle);
	res.y = a.x * sin(angle) + a.y * cos(angle);
	res.z = a.z;
	return (res);
}
