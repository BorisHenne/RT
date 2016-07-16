/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:03:04 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/16 02:07:28 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

double	find_sphere_det(t_ray ray, t_sphere sphere, double *a, double *b)
{
	double c;
	t_vec tmp;

	*a = dot_product(ray.dir, ray.dir);

	tmp = vec_sub(sphere.center, ray.pos);
	*b = 2.0 * dot_product(ray.dir, tmp);

	c = dot_product(tmp, tmp) - pow(sphere.radius, 2);
	return (pow(*b, 2) - (4 * (*a) * c));
}

double	find_sphere_closest_hit(double a, double b, double det)
{
	double t1;
	double t2;

	t1 = (int)((-b + sqrt(det)) / (2 * a) * PRECISION);
	t1 /= (double)PRECISION;

	t2 = (int)((-b - sqrt(det)) / (2 * a) * PRECISION);
	t2 /= (double)PRECISION;


	if (t1 <= 0.0 && t2 <= 0.0)
		return -1.0;
	if (t1 <= 0.0)
		return (t2);
	else if (t2 <= 0.0)
		return (t1);
	else
		return (t1 < t2 ? t1 : t2);
}

t_coord	is_sphere_hit(t_ray ray, t_sphere sphere)
{
	t_coord hit;
	double det;
	double a;
	double b;

	hit.bool = 0;
	hit.t = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	/* calcul determinant */
	if (sphere.radius > 0.0)
	{
		det = find_sphere_det(ray, sphere, &a, &b);
		if (det == 0)
		{
			/* une solution unique */
			hit.t = (-b / (2 * a));
			hit.bool = hit.t > 0.0 ? 1 : 0;
			hit.color = sphere.color;
			hit.point_norm = normalize(vec_sub(sphere.center, vec_add(ray.pos, scalar_product(ray.dir, hit.t))));

		}
		else if (det > 0)
		{
			/* deux solutions */
			hit.t = find_sphere_closest_hit(a, b, det);
			hit.bool = hit.t > 0.00 ? 1 : 0;
			hit.color = sphere.color;
			hit.point_norm = normalize(vec_sub(sphere.center, vec_add(ray.pos, scalar_product(ray.dir, hit.t))));

		}
	}
	return (hit);
}
