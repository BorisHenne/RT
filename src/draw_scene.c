/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/21 05:55:16 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_color		init_color(int r, int g, int b)
{
	t_color res;

	res.r = r < 0 ? 0 : r;
	res.r = r > 255 ? 255 : r;
	res.g = g < 0 ? 0 : g;
	res.g = g > 255 ? 255 : g;
	res.b = b < 0 ? 0 : b;
	res.b = b > 255 ? 255 : b;
	return (res);
}

double		deg_to_rad(double angle)
{
	double res;

	res = angle * M_PI / 180;
	return res;
}

int         put_pixel_on_image(void *img, int x, int y, t_color color)
{
	char    *data;
	int     i;
	int     bpp;
	int     sl;
	int     endian;

	data = mlx_get_data_addr(img, &bpp, &sl, &endian);
	bpp /= 8;
	i = x * bpp + y * sl;
	if (x >= WIDTH || y >= HEIGHT)
		return (0);
	data[i] = color.b;
	data[i + 1] = color.g;
	data[i + 2] = color.r;
	return (0);
}

#include <stdio.h>

int		draw_scene(t_env *env, t_scene scene)
{
	int		x;
	int		y;
	int		r;
	t_ray	start;
	t_color final_color;
	float	reflet;
	t_hit	drawn_pixel;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			final_color = init_color(0,0,0);
			r = 0;
			start.pos = scene.cam.ray.pos;
			start.dir = calc_vec_dir(x, y, scene.cam, scene.cam.look_at);
			while (r < 2)
			{
				drawn_pixel = find_closest_object(scene.objects, start);
				if (drawn_pixel.bool == 1)
					drawn_pixel.color = apply_light(scene, drawn_pixel, start);
				else
					break;

				start.pos = vec_add(start.pos, scalar_product(start.dir, drawn_pixel.t)); 
				reflet = dot_product(start.dir, drawn_pixel.point_norm) * 2.0;
				start.dir = vec_sub(scalar_product(drawn_pixel.point_norm, reflet), start.dir);
				final_color = add_color(final_color, drawn_pixel.color);
				check_color(&final_color);
				r++;
			}
			put_pixel_on_image(env->img, x, y, final_color);
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
