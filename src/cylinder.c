/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:09:27 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/13 05:29:27 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cylinder.h>
#include <stdio.h>
#include <libft.h>

double	find_cylinder_det(t_cam cam, t_cylinder cylinder, double *a, double *b)
{
	(void)b;
	(void)a;
	double c;
	t_vec tmp;

	tmp = vec_sub(cylinder.pos, cam.pos);

	*a = pow(cam.dir.x, 2) + pow(cam.dir.y, 2);

	*b = 2.0 * (cam.dir.x * tmp.x + cam.dir.y * tmp.y);

	c = pow(tmp.x, 2) + pow(tmp.y, 2) - pow(cylinder.radius, 2);
	return (pow(*b, 2) - (4 * (*a) * c));

}


double	find_cylinder_heigth(t_cam cam, t_cylinder cylinder, double t1, double t2)
{
	double hit_z;

	hit_z = cam.pos.z + t1 * cam.dir.z;

	double max_heigth;

	max_heigth = cylinder.pos.z + cylinder.length;
	if (cylinder.pos.z <= hit_z && hit_z <= max_heigth)
		return t1;
	else
	{
		hit_z = cam.pos.z + t2 * cam.dir.z;

		max_heigth = cylinder.pos.z + cylinder.length;
		if (cylinder.pos.z <= hit_z && hit_z <= max_heigth)
			return t2;
		else
			return 0.0;
	}
}

double	find_cylinder_closest_hit(t_cam cam, t_cylinder cylinder, double a, double b, double det)
{
	double t1;
	double t2;

	t1 = (-b - sqrt(det)) / (2 * a);
	t2 = (-b + sqrt(det)) / (2 * a); 

	return (find_cylinder_heigth(cam, cylinder, t1, t2));
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
	if (cylinder.radius > 0 && cylinder.length != 0)
	{
		det = find_cylinder_det(cam, cylinder, &a, &b);
		if (det == 0)
		{
			// une solution unique 
			hit.bool = 1;
			hit.t = (-b / (2 * a));
			hit.color = cylinder.color;
		}
		else if (det > 0)
		{
			// deux solutions 
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
	return hit;
}
