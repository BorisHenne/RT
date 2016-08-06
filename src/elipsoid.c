/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elipsoid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 03:52:42 by tlepeche          #+#    #+#             */
/*   Updated: 2016/08/06 04:58:41 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double	find_elips_det(t_ray ray, t_elips elips, double *a, double *b)
{
	double c;
	t_vec tmp;

	*a = pow(ray.dir.x, 2) * pow(elips.quad.A, 2);
	*a += pow(ray.dir.y, 2) * pow(elips.quad.B, 2);
	*a += pow(ray.dir.z, 2) * pow(elips.quad.C, 2);

	tmp = vec_sub(elips.center, ray.pos);
	*b = tmp.x * ray.dir.x * pow(elips.quad.A, 2);
	*b += tmp.y * ray.dir.y * pow(elips.quad.B, 2);
	*b += tmp.z * ray.dir.z * pow(elips.quad.C, 2);
	*b *= 2.0;

	c = tmp.x * tmp.x * pow(elips.quad.A, 2);
	c += tmp.y * tmp.y * pow(elips.quad.B, 2);
	c += tmp.z * tmp.z * pow(elips.quad.C, 2);
	c -= pow(elips.radius, 2);

	return (pow(*b, 2) - (4 * (*a) * c));
}

void	find_elips_closest_hit(double a, double b, double det, t_hit *hit)
{
	double t1;
	double t2;

	t1 = (int)((-b + sqrt(det)) / (2 * a) * PRECISION);
	t1 /= (double)PRECISION;

	t2 = (int)((-b - sqrt(det)) / (2 * a) * PRECISION);
	t2 /= (double)PRECISION;

	if (t1 <= 0.0 && t2 <= 0.0)
	{
		hit->t = 0.0;
		hit->t_max = 0.0;
	}
	if (t1 <= 0.0)
	{
		hit->t = t2;
		hit->t_max = t1;
	}
	else if (t2 <= 0.0)
	{
		hit->t = t1;
		hit->t_max = t2;
	}
	else
	{
		hit->t = t1 < t2 ? t1 : t2;
		hit->t_max = t1 < t2 ? t2 : t1;
	}
}

t_hit	is_elips_hit(t_ray ray, t_elips elips)
{
	t_hit hit;
	double det;
	double a;
	double b;

	hit.bool = 0;
	hit.t = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	/* calcul determinant */
	if (elips.radius > 0.0)
	{
		det = find_elips_det(ray, elips, &a, &b);
		if (det == 0)
		{
			/* une solution unique */
			hit.t = (-b / (2 * a));
			hit.t_max = (-b / (2 * a));
			hit.bool = hit.t > 0.0 ? 1 : 0;
			hit.color = elips.color;

		}
		else if (det > 0)
		{
			/* deux solutions */
			find_elips_closest_hit(a, b, det, &hit);
			hit.bool = hit.t > 0.00 ? 1 : 0;
			hit.opacity = elips.opacity;
		}
		hit.type = ELIPS;
		hit.radius = elips.radius;
		hit.color = elips.color;

		ray.dir.x *= elips.quad.A * elips.quad.A;
		ray.dir.y *= elips.quad.B * elips.quad.B;
		ray.dir.z *= elips.quad.C * elips.quad.C;

		ray.pos.x *= elips.quad.A * elips.quad.A;
		ray.pos.y *= elips.quad.B * elips.quad.B;
		ray.pos.z *= elips.quad.C * elips.quad.C;

		hit.point_norm = normalize(vec_sub(elips.center, vec_add(ray.pos, scalar_product(ray.dir, hit.t))));
		hit.specular = elips.specular;
		hit.reflection = elips.reflection;
		hit.opacity = elips.opacity;
		hit.ref_index = elips.ref_index;
		hit.is_negativ = elips.is_negativ;
		hit.texture = elips.texture;
	}
	return (hit);
}
