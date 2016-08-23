/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 02:55:00 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/22 16:48:14 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

t_hit		init_hit(void)
{
	t_hit		hit;
	hit.t = 1000000;
	hit.t_max = 1000000;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	hit.bool = 0;
	hit.dist_from_center = -1.0;
	hit.length = -1.0;
	hit.opacity = 1;
	hit.is_negativ = 0;
	return (hit);
}

t_hit		get_hit(t_ray *ray, t_node *tmp, int is_neg)
{
	t_hit		tmp_content;

	tmp_content = init_hit();
	if (tmp->type == SPHERE && ((t_sphere *)(tmp->data))->is_negativ == is_neg)
		tmp_content = is_sphere_hit(ray, (t_sphere *)tmp->data);
	else if (tmp->type == CYLINDER && ((t_cylinder *)(tmp->data))->is_negativ == is_neg)
		tmp_content = is_cylinder_hit(ray, (t_cylinder *)tmp->data);
	else if (tmp->type == PLANE && ((t_plane *)(tmp->data))->is_negativ == is_neg)
		tmp_content = is_plane_hit(ray, (t_plane *)tmp->data);
	else if (tmp->type == CONE && ((t_cone *)(tmp->data))->is_negativ == is_neg)
		tmp_content = is_cone_hit(ray, (t_cone *)tmp->data);
	else if (tmp->type == ELIPS && ((t_elips *)(tmp->data))->is_negativ == is_neg)
		tmp_content = is_elips_hit(ray, (t_elips *)tmp->data);
	else if (tmp->type == TRIAN)
		tmp_content = is_trian_hit(ray, (t_triangle *)tmp->data);
	else if (tmp->type == PARA)
		tmp_content = is_parallelo_hit(ray, (t_parallelo *)tmp->data);
	return (tmp_content);
}

#include <stdio.h>
t_hit		find_closest_object(t_node *nodes, t_ray *ray)
{
	t_node		*tmp;
	t_hit		tmp_content;
	t_hit		negativ_hit;
	t_hit		closest_hit;


	closest_hit = init_hit();
	negativ_hit = init_hit();
	tmp = nodes;
	while (tmp)
	{
		tmp_content = get_hit(ray, tmp, 0);
		if (tmp_content.bool == 1)
		{
			if ((closest_hit.bool == 0 || tmp_content.t <= closest_hit.t) && tmp_content.t > 0)
			{
				closest_hit = tmp_content;
			}
		}
		tmp = tmp->next;
	}

	tmp = nodes;
	while (tmp)
	{
		tmp_content = get_hit(ray, tmp, 1);
		if (tmp_content.bool == 1 &&
		((closest_hit.t < tmp_content.t_max && closest_hit.t > tmp_content.t) ||
		(closest_hit.t_max > tmp_content.t && closest_hit.t_max < tmp_content.t_max) ||
		(closest_hit.t < tmp_content.t && closest_hit.t_max > tmp_content.t_max)))
		{
			if (negativ_hit.bool == 0)
				negativ_hit = tmp_content;
			else
			{
				if (tmp_content.t < negativ_hit.t && tmp_content.t_max < negativ_hit.t_max)
				{
					if (tmp_content.t_max > negativ_hit.t)
					{	
						negativ_hit.t = tmp_content.t;
						negativ_hit.point_norm = tmp_content.point_norm;
					}
					else
						negativ_hit = tmp_content;
				}
				else if (negativ_hit.t < tmp_content.t && negativ_hit.t_max < tmp_content.t_max && negativ_hit.t_max >= tmp_content.t)
				{
					negativ_hit.t_max = tmp_content.t_max;
					negativ_hit.point_norm_max = tmp_content.point_norm_max;
				}
				else if (tmp_content.t < negativ_hit.t && tmp_content.t_max > negativ_hit.t_max)
					negativ_hit = tmp_content;
			}
		}
		tmp = tmp->next;
	}

	if (negativ_hit.bool == 1)
	{
		if ((negativ_hit.t < closest_hit.t && negativ_hit.t_max < closest_hit.t_max && closest_hit.t < negativ_hit.t_max))
		{
			if (negativ_hit.type == PLANE)	
				closest_hit.point_norm = scalar_product(negativ_hit.point_norm, -1);
			else
			{
				closest_hit.t = negativ_hit.t_max;
				closest_hit.point_norm = scalar_product(negativ_hit.point_norm_max, -1);
			}
		}
		else if (negativ_hit.t > closest_hit.t && negativ_hit.t_max > closest_hit.t_max && closest_hit.t_max > negativ_hit.t)
		{
			closest_hit.t_max = negativ_hit.t;
			closest_hit.point_norm_max = scalar_product(negativ_hit.point_norm, -1);
		}
		else if (negativ_hit.t <= closest_hit.t && negativ_hit.t_max >= closest_hit.t_max)
		{
			ray->pos = vec_add(ray->pos, scalar_product(ray->dir, closest_hit.t_max));
			closest_hit = find_closest_object(nodes, ray);
		}
	}
	return (closest_hit);
}
