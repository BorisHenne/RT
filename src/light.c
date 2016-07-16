/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:43:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/16 04:34:40 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>
//t_color		apply_shadow(t_coord *curr_px, t_vec obj_pos, t_vec light_pos)
//{
//	t_ray	light_ray;
//	t_vec	norm_obj_point;
//	double	angle;
//	double	new_color;
//	t_color	tmp_color;
//
//	light_ray.pos = light_pos;
//	light_ray.dir = normalize(vec_sub(obj_pos, light_pos));
//	norm_obj_point = normalize(vec_sub(curr_px->point_norm, light_ray.dir));
//	angle = acos(dot_product(light_ray.dir, norm_obj_point));
//	new_color = 175;
////	printf("new_color : %f, angle : %f\n", new_color, angle);
//	if (curr_px->color.r - new_color <= 255 && curr_px->color.r - new_color >= 0.0)
//		curr_px->color.r -= new_color;
//	else if (curr_px->color.r - new_color > 255)
//		curr_px->color.r = 255;
//	else
//		curr_px->color.r = 0;
//	if (curr_px->color.g - new_color <= 255 && curr_px->color.g - new_color >= 0.0)
//		curr_px->color.g -= new_color;
//	else if (curr_px->color.g - new_color > 255)
//		curr_px->color.g = 255;
//	else
//		curr_px->color.g = 0;
//	if (curr_px->color.b - new_color <= 255 && curr_px->color.b - new_color >= 0.0)
//		curr_px->color.b -= new_color;
//	else if (curr_px->color.b - new_color > 255)
//		curr_px->color.b = 255;
//	else
//		curr_px->color.b = 0;
//}

t_color		add_color(t_color a, t_color b, t_color ref)
{
	t_color	res;

	if ((a.r + b.r) / 2 <= ref.r)
		res.r = (a.r + b.r) / 2;
	else
		res.r = ref.r;
	if ((a.g + b.g) / 2 <= ref.g)
		res.g = (a.g + b.g) / 2;
	else
		res.g = ref.g;
	if ((a.b + b.b) / 2 <= ref.b)
		res.b = (a.b + b.b) / 2;
	else
		res.b = ref.b;
	return (res);
}

t_color		diffuse_light(t_coord *curr_px, t_vec obj_pos, t_vec light_pos, t_coord tmp_content)
{
	t_ray	light_ray;
//	t_vec	norm_obj_point;
	double	angle;
	double	new_color;
	t_color	tmp_color;
//	t_vec test;

	(void)tmp_content;
	light_ray.pos = light_pos;
	light_ray.dir = vec_sub(obj_pos, light_pos);
//	test = vec_add(light_ray.pos, scalar_product(light_ray.dir, tmp_content.t));

//	norm_obj_point = normalize(vec_sub(curr_px->point_norm, light_ray.dir));
	angle = dot_product(normalize(light_ray.dir), normalize(curr_px->point_norm)) / (get_length(light_ray.dir) * get_length(curr_px->point_norm));
//	angle = dot_product(normalize(test), normalize(curr_px->point_norm)) / (get_length(test) * get_length(curr_px->point_norm));
	angle = acos(angle);
	if (angle == 0.0 || angle == M_PI)
		printf("angle : %f\n", angle);
	angle = 1 - angle;
//	if (angle > 0.0)
//		angle = /*(tmp_content.bool == 1 && tmp_content.t > 0.0) ? angle :*/ angle;
	new_color = angle * 255;
	//	printf("new_color : %f, angle : %f\n", new_color, angle);
	if (curr_px->color.r <= 255 && curr_px->color.r > 0.0)
		tmp_color.r = new_color;
	else
		tmp_color.r = 0;
//	else if (/*curr_px->color.r **/ new_color > 255)
//		curr_px->color.r = 255;
//	else
//		curr_px->color.r = 0;
//	new_color = fabs(curr_px->color.g * angle);
	if (curr_px->color.g <= 255 && curr_px->color.g > 0.0)
		tmp_color.g = new_color;
	else
		tmp_color.g = 0;
//	else if (curr_px->color.g * new_color > 255)
//		curr_px->color.g = 255;
//	else
//		curr_px->color.g = 0;
//	new_color = fabs(curr_px->color.b * angle);
	if (curr_px->color.b <= 255 && curr_px->color.b > 0.0)
		tmp_color.b = new_color;
	else
		tmp_color.b = 0;
//	else if (/*curr_px->color.b **/ new_color > 255)
//		curr_px->color.b = 255;
//	else
//		curr_px->color.b = 0;
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

	tmp_color.r = 0;
	tmp_color.g = 0;
	tmp_color.b = 0;
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
//					apply_shadow(&curr_pixel, obj_pos, ((t_light *)(tmp_light->data))->pos);
//				//	break ;
//			}
//			if (tmp_content.bool == 0)
//			{
		  			tmp_color = /*add_color(*/diffuse_light(&curr_pixel, obj_pos, ((t_light *)(tmp_light->data))->pos, tmp_content)/*, tmp_color, curr_pixel.color)*/;
//					if (tmp_content.bool == 1 && tmp_content.t > 0.0)
						break ;
//			}
			tmp_object = tmp_object->next;
		}
		tmp_light = tmp_light->next;	
	}
	curr_pixel.color = tmp_color;
	return (curr_pixel);
}
