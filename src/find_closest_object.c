/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 02:55:00 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/16 16:24:25 by nbelouni         ###   ########.fr       */
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

t_hit		get_hit(t_ray *ray, t_node *tmp)
{
	t_hit		tmp_content;

	tmp_content = init_hit();
	if (tmp->type == SPHERE)
		tmp_content = is_sphere_hit(ray, (t_sphere *)tmp->data);
	else if (tmp->type == CYLINDER)
		tmp_content = is_cylinder_hit(ray, (t_cylinder *)tmp->data);
	else if (tmp->type == PLANE)
		tmp_content = is_plane_hit(ray, (t_plane *)tmp->data);
	else if (tmp->type == CONE)
		tmp_content = is_cone_hit(ray, (t_cone *)tmp->data);
	else if (tmp->type == ELIPS)
		tmp_content = is_elips_hit(ray, (t_elips *)tmp->data);
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
//	printf("nouvelle boucle      ");
	while (tmp)
	{
		tmp_content = get_hit(ray, tmp);
		if (tmp_content.bool == 1)
		{
			if (tmp_content.is_negativ == 1)
			{
				negativ_hit = tmp_content;
			}
			else if ((closest_hit.bool == 0 || tmp_content.t <= closest_hit.t) && tmp_content.t > 0)
			{
				closest_hit = tmp_content;
			}
		}
		tmp = tmp->next;
	}
	if (negativ_hit.bool == 1)
	{
			//printf("type : %d\n", closest_hit.type);

		if ((negativ_hit.t < closest_hit.t && negativ_hit.t_max < closest_hit.t_max && closest_hit.t < negativ_hit.t_max))
		{
			closest_hit.t = negativ_hit.t_max + 0.01;
//			printf("1\n");
			if (negativ_hit.type == SPHERE || negativ_hit.type == ELIPS)
				closest_hit.point_norm = normalize(vec_sub(vec_add(ray->pos, scalar_product(ray->dir, negativ_hit.t_max)), negativ_hit.pos));
		}
		else if (negativ_hit.t > closest_hit.t && negativ_hit.t_max > closest_hit.t_max && closest_hit.t_max > negativ_hit.t)
		{
//			printf("2\n");
			closest_hit.t_max = negativ_hit.t - 0.01;
			if (negativ_hit.type == SPHERE || negativ_hit.type == ELIPS)
				closest_hit.point_norm = normalize(vec_sub(vec_add(ray->pos, scalar_product(ray->dir, negativ_hit.t_max)), negativ_hit.pos));
		}
		else if (negativ_hit.t <= closest_hit.t && negativ_hit.t_max >= closest_hit.t_max)
		{
//			printf("3\n");
			ray->pos = vec_add(ray->pos, scalar_product(ray->dir, closest_hit.t_max));
			closest_hit = find_closest_object(nodes, ray);
		}
		else
		{
//			printf("__________4\n");
//			printf("NEG : bool : %d, t : %f, t_max : %f\n", negativ_hit.bool, negativ_hit.t, negativ_hit.t_max);
//			printf("CLOSE : bool : %d, t : %f, t_max : %f\n", closest_hit.bool, closest_hit.t, closest_hit.t_max);
//			sleep(1);
		}
	}
//	printf("final t = %f\n\n", closest_hit.t);
	return (closest_hit);
}
