/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 04:42:45 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/23 17:11:59 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <cylinder.h>
#include <stdio.h>

static void	complete_hit(t_hit *hit, t_cylinder *cylinder)
{
	hit->type = CYLINDER;
	hit->radius = cylinder->radius;
	hit->length = cylinder->length;
	hit->color.r = cylinder->color.r;
	hit->color.g = cylinder->color.g;
	hit->color.b = cylinder->color.b;
	hit->opacity = cylinder->opacity;
	hit->ref_index = cylinder->ref_index;
	hit->specular = cylinder->specular;
	hit->reflection = cylinder->reflection;
	hit->texture = cylinder->texture;
	hit->is_negativ = cylinder->is_negativ;
}

t_hit	create_disk(t_ray *ray, t_cylinder *cylinder, double side)
{
	t_hit	hit;
	t_plane	*plane;
	t_vec	new_dir;
	t_vec	inter;

	plane = (t_plane *)malloc(sizeof(t_plane));
	new_dir = scalar_product(cylinder->dir, side);
	plane->pos = vec_add(cylinder->pos, scalar_product(new_dir, cylinder->length / 2.0));
	plane->normal = scalar_product(new_dir, -1);
	hit.t = find_plane_hit(ray, plane);
	hit.bool = 0;

	if (hit.t > (double)(1.0 / PRECISION))
	{
		inter = vec_add(ray->pos, scalar_product(ray->dir, hit.t));
		if (get_length(vec_sub(plane->pos, inter)) <= cylinder->radius)
		{
			hit.bool = 1;
			hit.point_norm = new_dir;			
		}
	}
	free(plane);
	return (hit);
}

double	find_cylinder_limit(t_ray *ray, t_cylinder *cylinder, double t, t_intern intern, t_hit *hit)
{
	t_vec	inter;
	t_vec	proj;
	double	tmp;

	inter = vec_add(ray->pos, scalar_product(ray->dir, t));
	proj = vec_sub(intern.aa, inter);
	tmp = dot_product(intern.ab, proj) / intern.ab2;
	intern.ab = scalar_product(intern.ab, tmp);
	intern.ab = vec_add(intern.ab, intern.aa);

	tmp = get_length(vec_sub(cylinder->pos, intern.ab));
	hit->dist_from_center = (tmp > cylinder->length / 2) ? 0 : tmp;
	if (tmp > cylinder->length / 2)
		return (0.0);
	hit->point_norm = inter;
	hit->point_norm = vec_sub(intern.ab, hit->point_norm);
	hit->point_norm = normalize(hit->point_norm);
	return (t);
}

double	find_cylinder_det(t_cylinder *cylinder, t_intern intern, double* t1, double *t2)
{
	double	a;
	double	b;
	double	c;
	double	det;

	a = dot_product(intern.v, intern.v);
	b = 2.0 * dot_product(intern.v, intern.oxb);
	c = dot_product(intern.oxb, intern.oxb) - (cylinder->radius * cylinder->radius  * intern.ab2);

	det = b * b - 4 * a * c;
	*t1 = (-b - sqrt(det)) / (2 * a);
	*t2 = (-b + sqrt(det)) / (2 * a);
	return (det);
}

t_hit	is_cylinder_hit(t_ray *ray, t_cylinder *cylinder)
{
	t_hit		hit;
	t_hit		hit_size;
	t_intern	intern;
	t_hit		hit_max;
	double		t1;
	double		t2;
	double		t_max;
	double		t;

	hit.bool = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	hit.t_max = 0;
	hit_max = hit;

	cylinder->dir = normalize(cylinder->dir);
	intern.aa = vec_add(cylinder->pos, cylinder->dir);
	intern.ab = vec_sub(cylinder->pos, intern.aa);
	intern.v = vec_sub(intern.aa, ray->pos);
	intern.oxb = cross_product(intern.v, intern.ab);
	intern.v = cross_product(ray->dir, intern.ab);
	intern.ab2 = dot_product(intern.ab, intern.ab);

	if (find_cylinder_det(cylinder, intern, &t1, &t2) >= 0)
	{
		if (cylinder->is_closed == 1)
		{
			// disk 1 et 2;
			hit_size = create_disk(ray, cylinder, -1);
			hit = create_disk(ray, cylinder, 1);

			if (hit.bool != 0)
			{
				if (hit_size.bool == 0)
				{
					hit_size.bool = 1;
					hit_size.t = hit.t;
					hit_size.point_norm = hit.point_norm;
				}
				else
				{
					if (hit_size.t < hit.t)
					{
						hit.t_max = hit.t;
						hit.t = hit_size.t;
						hit.point_norm_max = hit.point_norm;
						hit.point_norm = hit_size.point_norm;
					}
					else
					{
						hit.t_max = hit_size.t;
						hit.point_norm_max = hit_size.point_norm;
					}
					complete_hit(&hit, cylinder);
					return (hit);
				}
			}
		}

		t = t1 < t2 ? t1 : t2;
		t_max = t1 < t2 ? t2 : t1;

		t_max = find_cylinder_limit(ray, cylinder, t_max, intern, &hit_max);
		hit.point_norm_max = hit_max.point_norm;
		t = find_cylinder_limit(ray, cylinder, t, intern, &hit);
		hit_max.point_norm_max = hit.point_norm;
		if (t > (double)(1.0 / PRECISION))
		{
			hit.bool = 1;
			if (hit_size.bool == 1 && cylinder->is_closed == 1)
			{
				hit.t = t < hit_size.t ? t : hit_size.t;
				hit.t_max = t < hit_size.t ? hit_size.t : t;
				hit.point_norm_max = t < hit_size.t ? hit_size.point_norm : hit.point_norm;
				hit.point_norm = t < hit_size.t ? hit.point_norm : hit_size.point_norm;
			}
			else
			{
				hit.t = t;
				hit.t_max = t_max;
			}
			complete_hit(&hit, cylinder);
			return (hit);
		}
		else
		{
			hit = hit_max;
			if (t_max > (double)(1.0 / PRECISION))
			{
				hit.bool = 1;
				if (hit_size.bool == 1 && cylinder->is_closed == 1)
				{
					hit.t = t_max < hit_size.t ? t_max : hit_size.t;
					hit.t_max = t_max < hit_size.t ? hit_size.t : t_max;
					hit.point_norm = t_max < hit_size.t ? hit.point_norm : hit_size.point_norm;
					hit.point_norm_max = t_max < hit_size.t ? hit_size.point_norm : hit.point_norm;
				}
				else
				{
					hit.t = t_max;
					hit.t_max = t_max;
				}
				complete_hit(&hit, cylinder);
				return (hit);
			}
		}
		if ((hit_size.t_max < (double)(1.0 / PRECISION) || hit.t_max < (double)(1.0 / PRECISION))
				&& cylinder->is_closed == 1)
		{
			hit = hit_size;
			hit.t_max = hit.t;
		}
		complete_hit(&hit, cylinder);
	}
	return (hit);
}
