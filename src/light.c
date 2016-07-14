/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:43:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/14 03:23:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>
void		apply_shadow(t_color *color)
{
	if (color->r - 50 >= 0)
		color->r -= 50;
	if (color->g - 50 >= 0)
		color->g -= 50;
	if (color->b - 50 >= 0)
		color->b -= 50;
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
		//light_ray.pos = ((t_light *)(tmp_light->data))->pos;
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
		if (tmp_content.bool == 1 && tmp_content.t > 0)
		{
//			if (tmp_content.t == 45.0)
//				ft_putstr("LOLOLOLOLOLOL\n");
			apply_shadow(&(curr_pixel.color));
			break ;
//			if (tmp_content.t > curr_pixel.t /*&& tmp_content.t > 0*/)
		}
			tmp_object = tmp_object->next;
		}
		tmp_light = tmp_light->next;	
	}
	return (curr_pixel);
}
