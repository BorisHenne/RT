/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/19 07:07:39 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

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

	t_coord		drawn_pixel;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			scene.cam.ray.dir = calc_vec_dir(x, y, scene.cam, scene.cam.look_at);
			drawn_pixel = find_closest_object(scene.objects, scene.cam.ray);
			if (drawn_pixel.bool == 1)
			{
				drawn_pixel = apply_light(scene, drawn_pixel, scene.cam.ray);
			}
			put_pixel_on_image(env->img, x, y, drawn_pixel.color);
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
