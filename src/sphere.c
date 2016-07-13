/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:03:04 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/13 05:14:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

double	find_sphere_det(t_cam cam, t_sphere sphere, double *a, double *b)
{
	double c;
	t_vec tmp;

	*a = dot_product(cam.dir, cam.dir);;

	tmp = vec_sub(sphere.center, cam.pos);
	*b = 2.0 * dot_product(cam.dir, tmp);

	c = dot_product(tmp, tmp) - pow(sphere.radius, 2);
	return (pow(*b, 2) - (4 * (*a) * c));
}

double	find_sphere_closest_hit(double a, double b, double det)
{
	double t1;
	double t2;

	t1 = (-b + sqrt(det)) / (2 * a);
	t2 = (-b - sqrt(det)) / (2 * a); 

	/* retourne la valeur la plus proche de 0 car c'est la plus pres de la cam */
	if (t1 < 0 && t2 < 0)
		return (t1 < t2 ? t2 : t1);
	return (t1 < t2 ? t1 : t2);
}

t_coord	is_sphere_hit(t_cam cam, t_sphere sphere)
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
		det = find_sphere_det(cam, sphere, &a, &b);
		if (det == 0)
		{
			/* une solution unique */
			hit.bool = 1;
			hit.t = (-b / (2 * a));
			hit.color = sphere.color;
		}
		else if (det > 0)
		{
			/* deux solutions */
			hit.bool = 1;
			hit.t = find_sphere_closest_hit(a, b, det);
			hit.color = sphere.color;
		}
	}
	return (hit);
}
