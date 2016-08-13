/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 04:58:48 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/13 06:45:28 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

t_ray	find_refract_vect(t_ray start_ray, t_hit drawn_pixel, double c_r, int test)
{
	double	ref_refract;
	double new_ref_index;
	t_ray	res;	
	t_vec new_norm;

	res.pos = vec_add(start_ray.pos, scalar_product(start_ray.dir, drawn_pixel.t));

	drawn_pixel.point_norm = scalar_product(drawn_pixel.point_norm, test);

	ref_refract = dot_product(drawn_pixel.point_norm, start_ray.dir);
	ref_refract = c_r * sqrt(1 - ref_refract * ref_refract);
//	ref_refract = cos(asin(c_r * ref_refract));
	ref_refract = sqrt(1 - ref_refract * ref_refract);

	new_ref_index = ref_refract + c_r * dot_product(start_ray.dir, drawn_pixel.point_norm);
	new_norm = scalar_product(drawn_pixel.point_norm, new_ref_index);
	res.dir = scalar_product(start_ray.dir, c_r);
	res.dir = normalize(vec_sub(new_norm, res.dir)); 
	return (res);
}

t_color		apply_refraction(t_ray start, t_scene scene, t_hit drawn_pixel, double noise)
{
	double	refract_indice;
	t_color	tmp_color;
	int test;

	tmp_color = drawn_pixel.color;
//	if (drawn_pixel.opacity < 1.0)
	{
		if (drawn_pixel.t_max == drawn_pixel.t)
		{
			test = -1;
			refract_indice = drawn_pixel.ref_index;
		}
		else
		{
			test = 1;
			refract_indice = 1.0 / drawn_pixel.ref_index;
		}
//		printf("test=%d\n", test);
//		printf("avant: x=%f, y=%f,z=%f\n", start.dir.x, start.dir.y, start.dir.z);
		start = find_refract_vect(start, drawn_pixel, refract_indice, test);
//		printf("apres: x=%f, y=%f,z=%f\n\n", start.dir.x, start.dir.y, start.dir.z);
//		sleep(1);
	//	drawn_pixel = find_closest_object(scene.objects, start);
	//	if (drawn_pixel.bool == 1)
		{
			if (scene.is_real == CARTOON && is_black_edge(&drawn_pixel))
			{
				tmp_color = init_color(0, 0, 0);
				return (tmp_color);
			}
			else
				tmp_color = add_color(tmp_color, color_render(scene, start, noise));
		}
	}
//	check_color(&tmp_color);
	return (tmp_color);
}
