/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 04:58:48 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/23 01:04:46 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

t_ray	find_refract_vect(t_ray start_ray, t_hit drawn_pixel, double c_r, double next_r)
{
	double	norm_angle;
	double	ref_refract; //l'indice de refraction qui decoule des 2 premiers
	double	new_vect_angle;
	t_ray	res;	

	norm_angle = dot_product(normalize(start_ray.dir), drawn_pixel.point_norm) * -1;
	ref_refract = c_r / next_r;
	new_vect_angle = (float)sqrt(1 - (pow(ref_refract, 2) * (1 - pow(norm_angle, 2))));
	res.pos = vec_add(start_ray.pos, scalar_product(start_ray.dir, drawn_pixel.t)); 
	res.dir = normalize(vec_add(scalar_product(normalize(start_ray.dir), ref_refract), scalar_product(drawn_pixel.point_norm, (ref_refract * c_r) - ref_refract)));
//	printf("res : ");
//	write_vector(res.pos, "pos");
//	write_vector(res.dir, "dir");
	return (res);
}

t_hit	apply_opacity(t_ray start, t_scene scene, t_hit drawn_pixel, double reflet)
{
	double	refract_indice;
	int		is_in_object;
	t_color	tmp_color;

	is_in_object = 0;
//	tmp_color = mult_color(drawn_pixel.color, drawn_pixel.opacity);
	tmp_color = drawn_pixel.color;
	refract_indice = 1.0;
	while (drawn_pixel.opacity < 1.0)
	{
//		printf("avant : ");
//		write_vector(start.pos, "pos");
//		write_vector(start.dir, "dir");
		start = find_refract_vect(start, drawn_pixel, refract_indice, drawn_pixel.ref_index);
//		printf("apres : ");
//		write_vector(start.pos, "pos");
//		write_vector(start.dir, "dir");
		drawn_pixel = find_closest_object(scene.objects, start);
		if (drawn_pixel.bool == 1)
		{
			drawn_pixel.color = add_color(tmp_color, apply_light(scene, drawn_pixel, start));
			
			drawn_pixel.color = mult_color(drawn_pixel.color, reflet);
			if (is_in_object % 2 == 0)
			{
				refract_indice = drawn_pixel.ref_index;
				drawn_pixel.ref_index = 1.0;
			}
			else
			{
				refract_indice = 1.0;
			}
			is_in_object++;
		}
		else
		{
			drawn_pixel.color = tmp_color;
			break;
		}
	}
	return (drawn_pixel);

}
