/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:43:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/15 06:45:41 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>
void		apply_shadow(t_color *color)
{
	if (color->r - 20 >= 0)
		color->r -= 20;
	else
		color->r = 0.0;
	if (color->g - 20 >= 0)
		color->g -= 20;
	else
		color->g = 0.0;
	if (color->b - 20 >= 0)
		color->b -= 20;
	else
		color->b = 0.0;
}

void		diffuse_light(t_coord *curr_px, t_vec obj_pos, t_vec light_pos)
{
	t_ray	light_ray;
	t_vec	norm_obj_point;
	double	angle;
	double	new_color;

	light_ray.pos = light_pos;
	light_ray.dir = normalize(vec_sub(obj_pos, light_pos));
	norm_obj_point = normalize(vec_sub(curr_px->point_norm, light_ray.dir));
	angle = acos(dot_product(light_ray.dir, norm_obj_point));
//	if (angle > 0.0)
//	{
		new_color = 50 * angle;
//		printf("new_color : %f, angle : %f\n", new_color, angle);
		if (curr_px->color.r - new_color <= 255 && curr_px->color.r - new_color >= 0.0)
			curr_px->color.r -= new_color;
		else if (curr_px->color.r - new_color > 255)
			curr_px->color.r = 255;
		else
			curr_px->color.r = 0;
		if (curr_px->color.g - new_color <= 255 && curr_px->color.g - new_color >= 0.0)
			curr_px->color.g -= new_color;
		else if (curr_px->color.g - new_color > 255)
			curr_px->color.g = 255;
		else
			curr_px->color.g = 0;
		if (curr_px->color.b - new_color <= 255 && curr_px->color.b - new_color >= 0.0)
			curr_px->color.b -= new_color;
		else if (curr_px->color.b - new_color > 255)
			curr_px->color.b = 255;
		else
			curr_px->color.b = 0;
//	}
}

t_coord		apply_light(t_scene scene, t_coord curr_pixel, t_ray cam_ray)
{
	t_coord		tmp_content;
	t_node		*tmp_light;
	t_node		*tmp_object;
	t_ray		light_ray;
	t_vec		obj_pos;

	tmp_light = scene.lights;
	while (tmp_light)
	{
		obj_pos = vec_add(cam_ray.pos, scalar_product(cam_ray.dir, curr_pixel.t));
		light_ray.pos= obj_pos;
		light_ray.dir = normalize(vec_sub(light_ray.pos, ((t_light *)(tmp_light->data))->pos));
		tmp_object = scene.objects;
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
//			if (tmp_content.bool == 1 && tmp_content.t > 0.0)
//			{
//				apply_shadow(&(curr_pixel.color));
//				break ;
//			}
			if (tmp_content.bool == 0)
			{
				if (tmp_object->type == SPHERE) // le reste est pasencore implemente
				{
		  			diffuse_light(&curr_pixel, obj_pos, ((t_light *)(tmp_light->data))->pos);
					break ;
				}
			}
			tmp_object = tmp_object->next;
		}
		tmp_light = tmp_light->next;	
	}
	return (curr_pixel);
}
