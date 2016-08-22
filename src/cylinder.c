/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 04:42:45 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/17 20:00:37 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <cylinder.h>
#include <stdio.h>

void	complete_hit(t_hit *hit, t_cylinder *cylinder)
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
		if (get_length(vec_sub(plane->pos, inter)) < cylinder->radius)
		{
			hit.bool = 1;
			hit.point_norm = new_dir;			
		}
	}
	free(plane);
	return (hit);
}

double	find_cylinder_limit(t_ray *ray, t_cylinder *cylinder, double t, t_vec aa, t_vec ab, double ab2, t_hit *hit)
{
	t_vec	inter;
	t_vec	proj;
	double	time;
	double	tmp;

	time = t;
	if (time < (double)(1.0 / PRECISION))
		return (0.0f);
	inter = scalar_product(ray->dir, time);
	inter = vec_add(inter, ray->pos);
	proj = vec_sub(aa, inter);
	tmp = dot_product(ab, proj) / ab2;
	ab = scalar_product(ab, tmp);
	ab = vec_add(ab, aa);
	//
	proj.x = ab.x;
	proj.y = ab.y;
	proj.z = ab.z;
	//
	tmp = get_length(vec_sub(cylinder->pos, proj));
	hit->dist_from_center = (tmp > cylinder->length / 2) ? 0 : tmp;
	if (tmp > cylinder->length / 2)
		return (0.0);
	hit->point_norm = inter;
	hit->point_norm = vec_sub(proj, hit->point_norm);
	hit->point_norm = normalize(hit->point_norm);
	return (time);
}

t_hit	is_cylinder_hit(t_ray *ray, t_cylinder *cylinder)
{
	t_hit	hit;
	t_hit	hit_size;
	t_vec	aa;
	t_vec	ab;
	t_vec	oxb;
	t_vec	v;
	double	ab2;
	//
	double	a, b, c;
	double	det, t1, t2;
	double	t_max, t;
	double	time1;
	double	time2;

	hit.bool = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	hit.t_max = 0;

	cylinder->dir = normalize(cylinder->dir);
	aa = vec_add(cylinder->pos, cylinder->dir);
	ab = vec_sub(cylinder->pos, aa);
	v = vec_sub(aa, ray->pos);
	oxb = cross_product(v, ab);
	v = cross_product(ray->dir, ab);
	ab2 = dot_product(ab, ab);
	a = dot_product(v, v);
	b = 2.0 * dot_product(v, oxb);
	c = dot_product(oxb, oxb) - (cylinder->radius * cylinder->radius  * ab2);
	det = b * b - 4 * a * c;

	if (det >= 0)
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
//				hit_size.point_norm_max = hit.point_norm;
				hit_size.point_norm = hit.point_norm;
			}
			else
			{
				// 2 disk toucher donc on touchera pas un cote
				// -> on passe tout dans struct hit car t1 et t2 seront < 0
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
		t1 = (-b - sqrt(det)) / (2 * a);
		t2 = (-b + sqrt(det)) / (2 * a);

		t = t1 < t2 ? t1 : t2;
		t_max = t1 < t2 ? t2 : t1;

		t_hit hit_max;
		time2 = find_cylinder_limit(ray, cylinder, t_max, aa, ab, ab2, &hit_max);
		hit.point_norm_max = hit_max.point_norm;
		time1 = find_cylinder_limit(ray, cylinder, t, aa, ab, ab2, &hit);
		hit_max.point_norm_max = hit.point_norm;
		if (time1 > (double)(1.0 / PRECISION))
		{
			hit.bool = 1;
			if (hit_size.bool == 1)
			{
				hit.t = time1 < hit_size.t ? time1 : hit_size.t;
				hit.t_max = time1 < hit_size.t ? hit_size.t : time1;
				hit.point_norm_max = time1 < hit_size.t ? hit_size.point_norm : hit.point_norm;
				hit.point_norm = time1 < hit_size.t ? hit.point_norm : hit_size.point_norm;
			}
			else
			{
				hit.t = time1;
				hit.t_max = t_max;
//				hit.point_norm_max = init_vector(0, 0, 0);
//				hit.point_norm_max = scalar_product(hit.point_norm, -1);
			}
			complete_hit(&hit, cylinder);
			return (hit);
		}
		else
		{
			t = (t == t1) ? t2 : t1;
			t_max = (t == t1) ? t1 : t2;	
			hit = hit_max;
			if (time2 > (double)(1.0 / PRECISION))
			{
//				t = (t == t1) ? t2 : t1;
//				t_max = (t_max == t1) ? t1 : t2;
				hit.bool = 1;
				if (hit_size.bool == 1)
				{
					hit.t = time2 < hit_size.t ? time2 : hit_size.t;
					hit.t_max = time2 < hit_size.t ? hit_size.t : time2;
					hit.point_norm = time2 < hit_size.t ? hit.point_norm : hit_size.point_norm;
					hit.point_norm_max = time2 < hit_size.t ? hit_size.point_norm : hit.point_norm;
				}
				else
				{
					hit.t = time2;
					hit.t_max = t_max;
	//				hit.point_norm_max = scalar_product(hit.point_norm, -1);
				}
				complete_hit(&hit, cylinder);
				return (hit);
			}
		}
		if (hit_size.t_max < (double)(1.0 / PRECISION) || hit.t_max < (double)(1.0 / PRECISION))
		{
			hit = hit_size;
			hit.t_max = hit.t;
		}
		complete_hit(&hit, cylinder);
	}
	return (hit);
}
