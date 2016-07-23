/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 04:58:48 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/23 16:09:03 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

t_ray	find_refract_vect(t_ray start_ray, t_hit drawn_pixel, double c_r, double next_r, int is_in_object)
{
//	double	norm_angle;
	double	ref_refract; //l'indice de refraction qui decoule de c_r et next_r
//	double	new_vect_angle;
	t_ray	res;	

	res = start_ray;
	res.pos = vec_add(start_ray.pos, scalar_product(start_ray.dir, drawn_pixel.t));
	/*norm_angle = dot_product((start_ray.dir), drawn_pixel.point_norm) * -1;
	ref_refract = c_r / next_r;
	new_vect_angle = 1 - pow(ref_refract, 2) * (1 - pow(norm_angle, 2));
		res.dir = normalize(vec_add(scalar_product((start_ray.dir), ref_refract), scalar_product(drawn_pixel.point_norm, (ref_refract * norm_angle - sqrt(new_vect_angle)))));
		res.pos = vec_add(start_ray.pos, scalar_product(start_ray.dir, drawn_pixel.t));
//		res.dir = normalize(vec_add(scalar_product((start_ray.dir), ref_refract), scalar_product(drawn_pixel.point_norm, (ref_refract * c_r - ref_refract))));*/




//	(void)c_r;
//	is_in_object = 0;
	double nr = c_r / next_r;
//	if (nr > 1)
//		nr -= 1;
	if (is_in_object % 2 == 1)
	{
		drawn_pixel.point_norm = (scalar_product(drawn_pixel.point_norm, -1.0));
	}
	ref_refract = dot_product(drawn_pixel.point_norm, scalar_product(start_ray.dir, 1));
	double racine;
	racine = (double)1.0 - (pow(nr, 2) * (1.0 - pow(ref_refract, 2)));
	if (racine < 0.0)
	{
		ft_putstr("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		racine *= -1;
	}
//	else
//	{
		res.pos = vec_add(start_ray.pos, scalar_product(start_ray.dir, drawn_pixel.t));
		t_vec new_norm;
		if (ref_refract >= 0.0)
			new_norm = (scalar_product(drawn_pixel.point_norm, (nr * ref_refract - (double)sqrt(racine))));
		else
			new_norm = (scalar_product(drawn_pixel.point_norm, (nr * ref_refract + (double)sqrt(racine))));
		res.dir = normalize(vec_sub(new_norm, (scalar_product(start_ray.dir, nr))));
//	}



		
	return (res);
}

t_hit	apply_opacity(t_ray start, t_scene scene, t_hit drawn_pixel, double reflet)
{
	double	refract_indice;
	int		is_in_object;
	t_color	tmp_color;

	(void)reflet;
	is_in_object = 0;
//	tmp_color = mult_color(drawn_pixel.color, drawn_pixel.opacity);
	tmp_color = drawn_pixel.color;
	refract_indice = 1.0;
	while (drawn_pixel.opacity < 1.0)
	{
		start = find_refract_vect(start, drawn_pixel, refract_indice, drawn_pixel.ref_index, is_in_object);
		drawn_pixel = find_closest_object(scene.objects, start);
//		write_vector(start.dir, "heelo");
//		printf("drawn_pixel.t : %f\n", drawn_pixel.t);
//		if (is_in_object % 2 == 1)
//		{
			if (drawn_pixel.bool == 1)
			{
				tmp_color = add_color(tmp_color, apply_light(scene, drawn_pixel, start));
//				drawn_pixel.color = mult_color(drawn_pixel.color, reflet);
			}
			else
			{
				break;
			}
//		}
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
	drawn_pixel.color = tmp_color;
	check_color(&drawn_pixel.color);
	return (drawn_pixel);

}
