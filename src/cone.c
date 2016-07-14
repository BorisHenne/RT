/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:24:52 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/14 03:32:22 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cone.h>

double		find_cone_det(t_ray ray, t_cone cone, double *a, double*b)
{
	double	c;
	t_vec	tmp;

	tmp = vec_sub(cone.pos, ray.pos);

	*a = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) - pow(ray.dir.z, 2);
	*b = 2.0  * (tmp.x * ray.dir.x + tmp.y * ray.dir.y - tmp.z * ray.dir.z);
	c = pow(tmp.x, 2) + pow(tmp.y, 2) - pow(tmp.z, 2);
	return (pow(*b, 2) - (4 * (*a) * c));
}

/*
double		find_cone_closest_hit(double a, double b, double det)
{
	double t1;
	double t2;

	t1 = ()
}
*/
#include <stdio.h>
t_coord		is_cone_hit(t_ray ray, t_cone cone)
{
	t_coord	hit;
	double	a;
	double	b;
	double	det;

	hit.bool = 0;
	hit.t = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;


	//if (cone_is_valid)
	//{
	det = find_cone_det(ray, cone, &a, &b);
	if (det == 0)
	{
		hit.bool = 1;
		hit.t = (-b / (2 * a));
		hit.color = cone.color;
		//printf("test %f\n", det);
	}
	else if (det > 0)
	{
		hit.bool = 1;
		hit.t = find_sphere_closest_hit(a, b, det);
		hit.color = cone.color;
		//printf("test %f\n", det);
	}
	//else
		//printf("test %f\n", det);
	//}
	return (hit);
}
