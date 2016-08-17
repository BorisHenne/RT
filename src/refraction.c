/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 04:58:48 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/17 03:59:41 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

t_ray	find_refract_vect(t_ray *start_ray, t_hit drawn_pixel, double c_r, int test)
{
	double	ref_refract;
	double	new_ref_index;
	t_ray	res;	
	t_vec	new_norm;
	t_vec	inv_dir;

	res.pos = vec_add(start_ray->pos, scalar_product(start_ray->dir, drawn_pixel.t));
	inv_dir = scalar_product(start_ray->dir, -1);
	drawn_pixel.point_norm = scalar_product(drawn_pixel.point_norm, test);
	ref_refract = dot_product(drawn_pixel.point_norm, inv_dir);
	ref_refract /= (get_length(drawn_pixel.point_norm) * get_length(inv_dir));
	new_ref_index =	1 - c_r * c_r * (1 - ref_refract * ref_refract);
	if (new_ref_index > 0)
	{
		new_ref_index = sqrt(new_ref_index);
		new_ref_index = c_r * ref_refract - new_ref_index;
		new_norm = scalar_product(drawn_pixel.point_norm, new_ref_index);
		res.dir = scalar_product(inv_dir, c_r);
		res.dir = vec_sub(res.dir, new_norm); 
	}
	else
		res.dir = init_vector(0, 0, 0);
	return (res);
}

t_color		apply_refraction(t_ray *start, t_scene *scene, t_hit drawn_pixel, double noise)
{
	double	refract_indice;
	t_color	tmp_color;
	int test;
	static int	a = 0;
	tmp_color = drawn_pixel.color;
	if (drawn_pixel.t_max == drawn_pixel.t)
	{
		if (a == 1)
			refract_indice = drawn_pixel.ref_index;
		else
			refract_indice = 1.0;
		test = -1;
		a = 0;
	}
	else
	{
		a = 1;
		test = 1;
		refract_indice = 1.0 / drawn_pixel.ref_index;
	}
	*start = find_refract_vect(start, drawn_pixel, refract_indice, test);
	if (get_length(start->dir) != 0)
	{
		if (scene->is_real == CARTOON && is_black_edge(&drawn_pixel))
		{
			tmp_color = init_color(0, 0, 0);
			return (tmp_color);
		}
		else
			tmp_color = add_color(tmp_color, color_render(scene, start, noise));
	}
	check_color(&tmp_color);
	return (tmp_color);
}
