/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/12 00:43:12 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
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
int		draw_scene(t_env *env)
{
	int		x;
	int		y;

	t_vec ori;
	ori.x = 0.0;
	ori.y = 0.0;
	ori.z = -3.0;
	t_vec look;
	look.x = 2.0;
	look.y = 7.0;
	look.z = 20.0;
	t_vec init_vec;
	init_vec.x = 0.0;
	init_vec.y = 1.0;
	init_vec.z = 0.0;
	t_cam cam;
	
	cam = init_camera(ori, look, init_vec);
	
	t_sphere	sphere;
	sphere.radius = 0.5;
	sphere.center.x = -1.0;
	sphere.center.y = 0.0;
	sphere.center.z = 20.0;
	sphere.color.r = 123;
	sphere.color.g = 0;
	sphere.color.b = 0;
	/*
	t_plan		plan;
	plan.pos.x = -2.0;
	plan.pos.y = -1.0;
	plan.pos.z = 0.0;	
	plan.norma.x = 1.0;
	plan.norma.y = 1.0;
	plan.normal.z = 1.0;
	if (!(plan.color = (t_color *)malloc(sizeof(t_color))))
		return(-1);
	plan.color->r = 0;
	plan.color->g = 0;
	plan.color->b = 123;

*/

	t_coord		drawn_pixel;
	(void)drawn_pixel;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			cam.dir = calc_vec_dir(x, y, cam);
			drawn_pixel = is_sphere_hit(cam, sphere);
			if (drawn_pixel.bool == 1 && drawn_pixel.t < 0.5)
				put_pixel_on_image(env->img, x, y, drawn_pixel.color);
			else
			{
				put_pixel_on_image(env->img, x, y, drawn_pixel.color);
			}
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
