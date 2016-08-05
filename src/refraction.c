/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 04:58:48 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/05 03:29:54 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

//t_ray	find_refract_vect(t_ray start_ray, t_hit drawn_pixel, double c_r, double next_r, int is_in_object)
t_ray	find_refract_vect(t_ray start_ray, t_hit drawn_pixel, double c_r, int is_in_object)
{
	double	ref_refract; //l'indice de refraction qui decoule de c_r et next_r
	double nr;
	t_ray	res;	
	double new_ref_index;
	t_vec new_norm;

	(void)is_in_object;
	res.pos = vec_add(start_ray.pos, scalar_product(start_ray.dir, drawn_pixel.t));
	nr = c_r / drawn_pixel.ref_index;

	res.dir = scalar_product(start_ray.dir, nr);
	t_vec inv_norm = (scalar_product(drawn_pixel.point_norm, -1.0));
	ref_refract = dot_product(inv_norm, start_ray.dir);
	new_ref_index = ref_refract + nr * dot_product(start_ray.dir, drawn_pixel.point_norm);
	new_norm = scalar_product(drawn_pixel.point_norm, new_ref_index);
	res.dir = vec_sub(new_norm, res.dir); 
	
	return (res);
}

t_color		apply_refraction(t_ray start, t_scene scene, t_hit drawn_pixel, double reflet, double noise)
{
	double	refract_indice;
	int		is_in_object;
	t_color	tmp_color;
	double	opacity;

	opacity = drawn_pixel.opacity;
	(void)reflet;
	is_in_object = 0;
	tmp_color = drawn_pixel.color;
	refract_indice = 1.0;
	while (drawn_pixel.opacity < 1.0)
	{
		//start = find_refract_vect(start, drawn_pixel, refract_indice, drawn_pixel.ref_index, is_in_object);
		start = find_refract_vect(start, drawn_pixel, refract_indice, is_in_object);
		drawn_pixel = find_closest_object(scene.objects, start);
		if (drawn_pixel.t_max > drawn_pixel.t)
		{
			if (drawn_pixel.bool == 1)
			{
				tmp_color = add_color(tmp_color, color_render(scene, start, noise));
			}
			else
				break;
		}
		if (drawn_pixel.t_max <= drawn_pixel.t)
		{
			refract_indice = 1.0;
		}
		else
		{
			refract_indice = drawn_pixel.ref_index;
			drawn_pixel.ref_index = 1.0;
		}
		is_in_object++;
	}
	check_color(&tmp_color);
	return (tmp_color);

}
