/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:24:52 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/22 01:32:26 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <cone.h>
#include <stdio.h>

double		find_cone_det(t_ray ray, t_cone cone, double *a, double*b)
{
	double	c;
	t_vec	tmp;

	tmp = vec_sub(cone.pos, ray.pos);
	*a = pow(ray.dir.x, 2) + pow(ray.dir.z, 2) - pow(ray.dir.y, 2) * pow(tan(cone.ang), 2);
	*b = 2.0  * (tmp.x * ray.dir.x + tmp.z * ray.dir.z - tmp.y * ray.dir.y * pow(tan(cone.ang), 2));
	c = pow(tmp.x, 2) + pow(tmp.z, 2) - pow(tmp.y, 2) * pow(tan(cone.ang), 2);
	
	
	/*
	*a = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) - pow(ray.dir.z, 2) * pow(tan(cone.ang), 2);
	*b = 2.0  * (tmp.x * ray.dir.x + tmp.y * ray.dir.y - tmp.z * ray.dir.z * pow(tan(cone.ang), 2));
	c = pow(tmp.x, 2) + pow(tmp.y, 2) - pow(tmp.z, 2) * pow(tan(cone.ang), 2);
	*/
	return (pow(*b, 2) - (4 * (*a) * c));
}

double		find_cone_heigth(t_ray ray, t_cone cone, double t1, double t2)
{
	double hit_y;
	double max_heigth;

	hit_y = ray.pos.y + t1 * ray.dir.y;
	max_heigth = cone.pos.y + cone.len;
	
	t1 = (int)(t1 * PRECISION);
	t1 /= (double)PRECISION;

	if (cone.pos.y <= hit_y && hit_y <= max_heigth && t1 != 0.0)
		return (t1);
	else
	{
			hit_y = ray.pos.y + t2 * ray.dir.y;
			max_heigth = cone.pos.y + cone.len;
			if (cone.pos.y <= hit_y && hit_y <= max_heigth)
				return (t2);
			else
				return (0.0f);
	}
}

double		find_cone_closest_hit(t_ray ray, t_cone cone, double a, double b, double det)
{
	double	t1;
	double	t2;

	t1 = (int)((-b - sqrt(det)) / (2.0f * a) * PRECISION);
	t1 /= (double)PRECISION;

	t2 = (int)((-b + sqrt(det)) / (2.0f * a) * PRECISION);
	t2 /= (double)PRECISION;
	return (find_cone_heigth(ray, cone, t1, t2));
}

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
		hit.relection = cone.reflection;
		hit.opacity = cone.opacity;
		hit.ref_index = cone.ref_index;
		//printf("test %f\n", det);
	}
	else if (det > 0)
	{
		if ((hit.t = find_cone_closest_hit(ray, cone, a, b, det)) != 0.0f)
		{
			hit.bool = 1;
			hit.color = cone.color;
			hit.relection = cone.reflection;
			hit.opacity = cone.opacity;
			hit.ref_index = cone.ref_index;
		}
		else
		{
			hit.bool = 0;
		}
		//printf("test %f\n", det);
	}
	//else
		//printf("test %f\n", det);
	//}
	return (hit);
}
