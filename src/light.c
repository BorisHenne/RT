/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:43:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/20 04:27:54 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

void		check_pixel(t_color *color)
{
	if (color->r < 0)
		color->r = 0;
	else if (color->r > 255)
		color->r = 255;

	if (color->g < 0)
		color->g = 0;
	else if (color->g > 255)
		color->g = 255;

	if (color->b < 0)
		color->b = 0;
	else if (color->b > 255)
		color->b = 255;
}

t_color		diffuse_light(t_coord *curr_px, t_ray light_ray, t_light *light, t_color color1)
{
	double	angle;
	t_color	tmp_color;
	t_color light_color;

	angle = dot_product(normalize(light_ray.dir), normalize(curr_px->point_norm));

	light_color.r = curr_px->color.r * angle * light->color.r;
	light_color.g = curr_px->color.g * angle * light->color.g;
	light_color.b = curr_px->color.b * angle * light->color.b;

	tmp_color.r = (color1.r + light_color.r);
	tmp_color.g = (color1.g + light_color.g);
	tmp_color.b = (color1.b + light_color.b);
	return (tmp_color);
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
	int			shadow;

	tmp_light = scene.lights;
	tmp_color.r = tmp_color.g = tmp_color.b = 0;
	obj_pos = vec_add(cam_ray.pos, scalar_product(cam_ray.dir, curr_pixel.t));
	light_ray.pos = obj_pos;
	while (tmp_light)
	{
		shadow = 0;
		tmp_light_ray = vec_sub(light_ray.pos, ((t_light *)(tmp_light->data))->pos);
		light_ray.length = get_length(tmp_light_ray);
		light_ray.dir = normalize(tmp_light_ray);
		tmp_object = scene.objects;
		tmp_content.t = 0;
		tmp_content.bool = 0;
		while (tmp_object)
		{
			if (tmp_object->type == SPHERE)
				tmp_content = is_sphere_hit(light_ray, *(t_sphere *)tmp_object->data);
			else if (tmp_object->type == CYLINDER)
				tmp_content = is_cylinder_hit(light_ray, *(t_cylinder *)tmp_object->data);
			else if (tmp_object->type == PLANE)
				tmp_content = is_plane_hit(light_ray, *(t_plane *)tmp_object->data);
			else if (tmp_object->type == CONE)
				tmp_content = is_cone_hit(light_ray, *(t_cone *)tmp_object->data);
			if (tmp_content.bool == 1 && tmp_content.t > 0.0 && tmp_content.t <= light_ray.length)
			{
				shadow = 1;
				break ;
			}
			tmp_object = tmp_object->next;
		}
		if (shadow == 0)
			tmp_color = diffuse_light(&curr_pixel, light_ray, ((t_light *)(tmp_light->data)), tmp_color);
		else
		{
/*			t_color light_color;
			light_color.r = curr_pixel.color.r * 0.1;
			light_color.g = curr_pixel.color.g * 0.1;
			light_color.b = curr_pixel.color.b * 0.1;

			tmp_color.r = (tmp_color.r + light_color.r);
			tmp_color.g = (tmp_color.g + light_color.g);
			tmp_color.b = (tmp_color.b + light_color.b);*/
		}
		check_pixel(&tmp_color);
		tmp_light = tmp_light->next;
	}
	curr_pixel.color = tmp_color;
	return (curr_pixel);
}
