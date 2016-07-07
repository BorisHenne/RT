/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:03:04 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/07 06:41:38 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_coord	is_hit(t_camera *cam, t_sphere *sphere)
{
	t_coord hit;
	double det;
	double a;
	double b;

	/* calcul determinant */
	det = find_det(cam, sphere, &a, &b);
	if (det < 0)
	{
		/* pas de solution */
		hit.bool = 0;
		hit.t = 0;
		hit->color.r = 0;
		hit->color.g = 0;
		hit->color.b = 0;
	}
	else if (det == 0)
	{
		/* une solution unique */
		hit.bool = 1;
		hit.t = (-b / (2 * a));
		hit->color = sphere->color;
	}
	else
	{
		/* deux solutions */
		hit.bool = 1;
		hit.t = find_closest_hit(a, b, det);
		hit->color = sphere->color;
	}
	return hit;
}

double	find_det(t_camera *cam, t_sphere *sphere, double *a, double *b)
{
	double c;

	*a = pow(cam->dir.x, 2) + pow(cam->dir.y, 2) + pow(cam->dir.z, 2);
	*b = 2.0 * (cam->dir.x * (cam->origin.x - sphere->center.x) +
		cam->dir.y * (cam->origin.y - sphere->center.y) +
		cam->dir.z * (cam->origin.z - sphere->center.z));
	c = pow((cam->origin.x - sphere->center.x), 2) +
		pow((cam->origin.y - sphere->center.y), 2) +
		pow((cam->origin.z - sphere->center.z), 2) -
		pow(sphere->radius, 2);

	return (pow(b, 2) - (4 * a * c));
}

double	find_closest_hit(double a, double b, double det)
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
