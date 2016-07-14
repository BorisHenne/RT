/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:24:52 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/14 05:39:18 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	double hit_z;
	double max_heigth;
/*
	hit_z = ray.pos.z + t1 * ray.dir.z;
	max_heigth = cone.pos.z + cone.len;
	if (cone.pos.z <= hit_z && hit_z <= max_heigth)
	{
		return (t1);
	}
	else
	{
			hit_z = ray.pos.z + t2 * ray.dir.z;
			max_heigth = cone.pos.z + cone.len;
			if (cone.pos.z <= hit_z && hit_z <= max_heigth)
				return (t2);
			else
				return (0.0f);
	}

	*/
	hit_z = ray.pos.y + t1 * ray.dir.y;
	max_heigth = cone.pos.y + cone.len;
	if (cone.pos.y <= hit_z && hit_z <= max_heigth)
	{
		return (t1);
	}
	else
	{
			hit_z = ray.pos.y + t2 * ray.dir.y;
			max_heigth = cone.pos.y + cone.len;
			if (cone.pos.y <= hit_z && hit_z <= max_heigth)
				return (t2);
			else
				return (0.0f);
	}
}

double		find_cone_closest_hit(t_ray ray, t_cone cone, double a, double b, double det)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(det)) / (2.0f * a);
	t2 = (-b + sqrt(det)) / (2.0f * a);
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
		//printf("test %f\n", det);
	}
	else if (det > 0)
	{
		if ((hit.t = find_cone_closest_hit(ray, cone, a, b, det)) != 0.0f)
		{
			hit.bool = 1;
			hit.color = cone.color;
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
