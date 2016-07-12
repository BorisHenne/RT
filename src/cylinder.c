/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:09:27 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/12 05:29:25 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cylinder.h>
#include <stdio.h>
#include <libft.h>

double	find_cylinder_det(t_cam cam, t_cylinder cylinder, double *a, double *b)
{
	double c;
	t_vec tmp;

	tmp = vec_sub(cam.pos, cylinder.pos);
	/* *a = dot_product(cam.dir, cam.dir) - pow(dot_product(cam.dir, cylinder.dir), 2);

	 *b = 2.0 * (dot_product(cam.dir, tmp) - dot_product(cam.dir, cylinder.dir) * dot_product(tmp, cylinder.dir));

	 c = dot_product(tmp, tmp) - pow(dot_product(tmp, cylinder.dir), 2) - pow(cylinder.radius, 2);*/

	*a = pow(cam.dir.x, 2) + pow(cam.dir.y, 2);
	*b = 2.0 * (cam.dir.x * tmp.x + cam.dir.y * tmp.y);
	c = pow(tmp.x, 2) + pow(tmp.y, 2) - pow(cylinder.radius, 2);

	return (pow(*b, 2) - (4 * (*a) * c));
}


double	find_cylinder_heigth(t_cam cam, t_cylinder cylinder, double near, double far)
{
	double hit_length;
	double res;

	hit_length = fabs(cam.pos.z + near * cam.dir.z);
//	printf("1st length = %.2f", hit_length);
	if (hit_length < cylinder.length && hit_length >= 0.0)
	{
		res = near;
	}
	else
	{
		hit_length = fabs(cam.pos.z + far * cam.dir.z);
		if (hit_length < cylinder.length && hit_length >= 0.0)
			res = far;
		else
			res = 0.0;
//		printf(", 2nd length = %.2f, res = %.2f", hit_length, res);
	}
//	printf("\n");
	return res;
}

double	find_cylinder_closest_hit(t_cam cam, t_cylinder cylinder, double a, double b, double det)
{
	double t1;
	double t2;

	t1 = (-b + sqrt(det)) / (2 * a);
	t2 = (-b - sqrt(det)) / (2 * a); 
	(void)cam;
	(void)cylinder;

/*		if (t1 < 0 && t2 < 0)
		return (t1 < t2 ? t2 : t1);
		return (t1 < t2 ? t1 : t2);*/
	if (t1 < t2)
		return (find_cylinder_heigth(cam, cylinder, t1, t2));
	else
		return (find_cylinder_heigth(cam, cylinder, t2, t1));
}

t_coord	is_cylinder_hit(t_cam cam, t_cylinder cylinder)
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
	if (cylinder.radius > 0/* && cylinder.lenght != 0*/)
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
			if ((hit.t = find_cylinder_closest_hit(cam, cylinder, a, b, det)) != 0.0)
			{
//				printf("t = %.2f\n", hit.t);
				hit.bool = 1;
				hit.color = cylinder.color;
			}
			else
			{
				hit.bool = 0;
			}
		}
	}
	return (hit);
}
