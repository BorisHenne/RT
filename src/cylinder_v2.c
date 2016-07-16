/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 04:42:45 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/16 05:42:45 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <cylinder.h>

double	find_cylinder_det(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

double	find_cylinder_limit(t_ray ray, t_cylinder cylinder, double t, t_vec aa, t_vec ab, double ab2)
{
	t_vec	inter;
	t_vec	proj;
	double	time;
	double	tmp;

	time = t;
	if (time < 0)
		return (0.0f);
	inter = scalar_product(ray.dir, time);
	inter = vec_add(inter, ray.pos);
	proj = vec_sub(aa, inter);
	tmp = dot_product(ab, proj) / ab2;
	ab = scalar_product(ab, tmp);
	ab = vec_add(ab, aa);
	//
	proj.x = ab.x;
	proj.y = ab.y;
	proj.z = ab.z;
	//
	proj = vec_sub(cylinder.pos, proj);
	tmp = get_length(proj);
	if (tmp > cylinder.length)
		return (0.0);
	else
		return (time);
}

t_coord	is_cylinder_hit(t_ray ray, t_cylinder cylinder)
{
	t_coord	hit;
	t_vec	aa;
	t_vec	ab;
	t_vec	oxb;
	t_vec	v;
	double	ab2;
	//
	double	a, b, c;
	double	det, t1, t2;
	double	time;

	hit.bool = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;

	aa = vec_add(cylinder.pos, cylinder.dir);
	ab = vec_sub(cylinder.pos, aa);
	v = vec_sub(aa, ray.pos);
	oxb = cross_product(v, ab);
	v = cross_product(ray.dir, ab);
	ab2 = dot_product(ab, ab);
	a = dot_product(v, v);
	b = 2.0 * dot_product(v, oxb);
	c = dot_product(oxb, oxb) - (cylinder.r * cylinder.r  * ab2);

	det = find_cylinder_det(a, b, c);
	if (det < 0)
		hit.bool = 0;
	else
	{
		t1 = (int)((-b - sqrt(det)) / (2 * a) * PRECISION);
		t1 /= (double)PRECISION;
		t2 = (int)((-b - sqrt(det)) / (2 * a) * PRECISION);
		t2 /= (double)PRECISION;
		time = find_cylinder_limit(ray, cylinder, t1, aa, ab, ab2);
		if (time > 0.0f)
		{
			hit.bool = 1;
			hit.t = time;
			hit.color.r = cylinder.color.r;
			hit.color.g = cylinder.color.g;
			hit.color.b = cylinder.color.b;
		}
		else
		{
			time = find_cylinder_limit(ray, cylinder, t2, aa, ab, ab2);
			if (time > 0.0f)
			{
				hit.bool = 1;
				hit.color.r = cylinder.color.r;
				hit.color.g = cylinder.color.g;
				hit.color.b = cylinder.color.b;
			}
		}
	}
	return (hit);
}