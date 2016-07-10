/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:09:27 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/10 05:05:59 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double	find_cylinder_det(t_cam *cam, t_cylinder *cylinder, double *a, double *b)
{
	double c;
	t_vec tmp;

	tmp = sub_vec(cam->ori, cylinder->ori);
	//X = cam->ori - cylinder->ori
	*a = dot_product(cam->dir, cam->dir) - pow(dot_product(cam->dir, cylinder->dir), 2);

	*b = 2.0 * (dot_product(cam->dir, tmp) - dot_product(cam->dir, cylinder->dir) * dot_product(tmp, cylinder->dir));

	c = dot_product(tmp, tmp) - pow(dot_product(tmp, cylinder->dir), 2) - pow(cylinder->radius, 2);

	return (pow(*b, 2) - (4 * (*a) * c));
}

double	find_cylinder_closest_hit(double a, double b, double det)
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

t_coord	is_cylinder_hit(t_cam *cam, t_cylinder *cylinder)
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
	if (cylinder->radius > 0 && cylinder->lenght != 0)
	{
		det = find_cylinder_det(cam, cylinder, &a, &b);
		if (det == 0)
		{
			/* une solution unique */
			hit.bool = 1;
			hit.t = (-b / (2 * a));
			hit.color = cylinder.color;
		}
		else if (det > 0)
		{
			/* deux solutions */
			hit.bool = 1;
			hit.t = find_cylinder_closest_hit(a, b, det);
			hit.color = cylinder.color;
		}
		return (hit);
	}
}
