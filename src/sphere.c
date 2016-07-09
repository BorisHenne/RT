/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:03:04 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/09 05:14:00 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	find_det(t_cam *cam, t_sphere *sphere, double *a, double *b)
{
	double c;
	t_vec *tmp;

	if (!(tmp = (t_vec *)malloc(sizeof(t_vec))))
		return (0);
	*a = dot_product(cam->dir, cam->dir);;

	tmp = sub_vec(&(sphere->center), cam->ori);
	*b = 2.0 * dot_product(cam->dir, tmp);

	tmp = sub_vec(&(sphere->center), cam->ori);
	c = dot_product(tmp, tmp) + pow(sphere->radius, 2);

	return (pow(*b, 2) - (4 * (*a) * c));
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

t_coord	is_hit(t_cam *cam, t_sphere *sphere)
{
	t_coord hit;
	double det;
	double a;
	double b;

	hit.color = (t_color *)malloc(sizeof(t_color));
	/* calcul determinant */
	det = find_det(cam, sphere, &a, &b);
	if (det < 0)
	{
//		ft_putendl("det < 0");
		/* pas de solution */
		hit.bool = 0;
		hit.t = 0;
		hit.color->r = 0;
		hit.color->g = 0;
		hit.color->b = 0;
	}
	else if (det == 0)
	{
//		ft_putendl("det == 0");
		/* une solution unique */
		hit.bool = 1;
		hit.t = (-b / (2 * a));
		hit.color = sphere->color;
	}
	else
	{
//		ft_putendl("det > 0");
		/* deux solutions */
		hit.bool = 1;
		hit.t = find_closest_hit(a, b, det);
		hit.color = sphere->color;
	}
	return hit;
}
