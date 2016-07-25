/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 04:58:48 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/24 13:27:37 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

t_ray	find_refract_vect(t_ray start_ray, t_hit drawn_pixel, double c_r, double next_r, int is_in_object)
{
	double	ref_refract; //l'indice de refraction qui decoule de c_r et next_r
	double nr;
	t_ray	res;	
	double new_ref_index;

	res = start_ray;
	res.pos = vec_add(start_ray.pos, scalar_product(start_ray.dir, drawn_pixel.t));
	nr = c_r / next_r;
	if (is_in_object % 2 == 1)
	{
		drawn_pixel.point_norm = (scalar_product(drawn_pixel.point_norm, -1.0));
	}
	ref_refract = dot_product(drawn_pixel.point_norm, scalar_product(start_ray.dir, 1));
	new_ref_index = (double)1.0 - (pow(nr, 2) * (1.0 - pow(ref_refract, 2)));
	res.pos = vec_add(start_ray.pos, scalar_product(start_ray.dir, drawn_pixel.t));
	t_vec new_norm;
	if (ref_refract >= 0.0)
		new_norm = (scalar_product(drawn_pixel.point_norm, (nr * ref_refract - (double)sqrt(new_ref_index))));
	else
		new_norm = (scalar_product(drawn_pixel.point_norm, (nr * ref_refract + (double)sqrt(new_ref_index))));
	res.dir = normalize(vec_sub(new_norm, (scalar_product(start_ray.dir, nr))));



		
	return (res);
}

t_color		apply_refraction(t_ray start, t_scene scene, t_hit drawn_pixel, double reflet)
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
		start = find_refract_vect(start, drawn_pixel, refract_indice, drawn_pixel.ref_index, is_in_object);
		drawn_pixel = find_closest_object(scene.objects, start);
		if (is_in_object % 2 == 1)
		{
//			drawn_pixel.opacity = 1 - opacity;
			if (drawn_pixel.bool == 1)
			{
				//drawn_pixel.color = mult_color(drawn_pixel.color, reflet);
				tmp_color = add_color(tmp_color, apply_light(scene, drawn_pixel, start));
			}
			else
			{
				break;
			}
		}
		if (is_in_object % 2 == 0)
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
//	printf("coucou");
	check_color(&tmp_color);
	return (tmp_color);

}
