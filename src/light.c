/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:43:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/17 04:05:10 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

t_color		diffuse_light(t_coord *curr_px, t_vec obj_pos, t_vec light_pos, t_coord tmp_content)
{
	t_ray	light_ray;
	double	angle;
	t_color	tmp_color;

	(void)tmp_content;
	light_ray.pos = light_pos;
	light_ray.dir = vec_sub(obj_pos, light_pos);
	angle = dot_product(light_ray.dir, curr_px->point_norm) / (get_length(light_ray.dir) * get_length(curr_px->point_norm));
	angle = acos(angle);
	angle = (int)(angle * PRECISION);
	angle /= (double)PRECISION;
	angle = (1 - (angle / M_PI));
	tmp_color.r = curr_px->color.r * angle;
	tmp_color.g = curr_px->color.g * angle;
	tmp_color.b = curr_px->color.b * angle;
	return (tmp_color);
}

t_color		add_color(t_color a, t_color b, t_color ref)
{
	if (b.r == ref.r && b.g == ref.g && b.b == ref.b)
		return a;

	if (a.r > b.r || a.g > b.g || a.b > b.b)
		return a;
	else
		return b;
}


t_color		apply_shadow(t_color ref, int n_shadows, int n_lights)
{
	t_color		shadow;
	t_color		res;

	shadow.r = 0;
	shadow.g = 0;
	shadow.b = 0;
	if (n_shadows == 0 || n_lights == 0)
		return (ref);
	res = ref;
	shadow.r = ref.r / n_lights;
	shadow.g = ref.g / n_lights;
	shadow.b = ref.b / n_lights;
	while (--n_shadows >= 0)
	{
		res.r = (res.r - shadow.r >= 0) ? res.r - shadow.r : 0;
		res.g = (res.g - shadow.g >= 0) ? res.g - shadow.g : 0;
		res.b = (res.b - shadow.b >= 0) ? res.b - shadow.b : 0;
	}
	return (res);
}

t_coord		apply_light(t_scene scene, t_coord curr_pixel, t_ray cam_ray)
{
	t_coord		tmp_content;
	t_node		*tmp_light;
	t_node		*tmp_object;
	t_ray		light_ray;
	t_vec		obj_pos;
	t_color		tmp_color;
	t_vec		tmp_light_ray;
	int			test_ombre;
	int			n_lights;

	tmp_light = scene.lights;
	tmp_color = curr_pixel.color;
	obj_pos = vec_add(cam_ray.pos, scalar_product(cam_ray.dir, curr_pixel.t));
	light_ray.pos = obj_pos;
	t_color test;
	test_ombre = 0;
	n_lights = 0;
	while (tmp_light)
	{
		tmp_light_ray = vec_sub(light_ray.pos, ((t_light *)(tmp_light->data))->pos);
		light_ray.length = get_length(tmp_light_ray);
		light_ray.dir = normalize(tmp_light_ray);
		tmp_object = scene.objects;
		tmp_content.t = 0;
		tmp_content.bool = 0;
		while (tmp_object)
		{
			if (curr_pixel.id != 0 && tmp_object->id != curr_pixel.id)
			{
				if (tmp_object->type == SPHERE)
					tmp_content = is_sphere_hit(light_ray, *(t_sphere *)tmp_object->data);
				else if (tmp_object->type == CYLINDER)
					tmp_content = is_cylinder_hit(light_ray, *(t_cylinder *)tmp_object->data);
				else if (tmp_object->type == PLANE)
					tmp_content = is_plane_hit(light_ray, *(t_plane *)tmp_object->data);
				else if (tmp_object->type == CONE)
					tmp_content = is_cone_hit(light_ray, *(t_cone *)tmp_object->data);
				// cas ou un autre objet se trouve entre le pts d'intersection et la lumiere
				// light_ray.length = longueur pts_touche->pos_spotlight
	  	  			if (tmp_content.bool == 1 && tmp_content.t > 0.0 && tmp_content.t <= light_ray.length)
					{
//						test.r = (tmp_color.r - 50) < 0 ? 0 : (tmp_color.r - 50) < 0 ;
//						test.g = (tmp_color.g - 50) < 0 ? 0 : (tmp_color.g - 50) < 0 ;
//						test.b = (tmp_color.b - 50) < 0 ? 0 : (tmp_color.b - 50) < 0 ;
						test_ombre += 1;
						break ;
					}
			}
			tmp_object = tmp_object->next;
		}
		test = diffuse_light(&curr_pixel, obj_pos, ((t_light *)(tmp_light->data))->pos, tmp_content);
		tmp_color = add_color(test, tmp_color, curr_pixel.color);
		tmp_light = tmp_light->next;
		n_lights += 1;
	}
	if (test_ombre)
		tmp_color = apply_shadow(tmp_color, test_ombre, n_lights);
	/*	if(test.g == 0 && test.b == 0)
		{
		printf("choose color: r = %d, g = %d, b = %d\n", tmp_color.r, tmp_color.g, tmp_color.b);
		printf("couleur ref: r = %d, g = %d, b = %d\n", curr_pixel.color.r, curr_pixel.color.g, tmp_color.b);
		printf("\n");
		}*/
	curr_pixel.color = tmp_color;
	return (curr_pixel);
}
