/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/14 05:38:16 by tlepeche         ###   ########.fr       */
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

int		draw_scene(t_env *env)
{
	int		x;
	int		y;

	t_vec ori;
	ori.x = 0.0;
	ori.y = 0.0;
	ori.z = -10.0;
	t_vec look;
	look.x = deg_to_rad(0);
	look.y = deg_to_rad(0);
	look.z = deg_to_rad(0);
	t_vec init_vec;
	init_vec.x = 0.0;
	init_vec.y = 1.0;
	init_vec.z = 0.0;
	t_cam cam;

	cam = init_camera(ori);

	t_sphere	sphere2;
	sphere2.radius = 0.3;
	sphere2.center.x = -1.0;
	sphere2.center.y = 0.5;
	sphere2.center.z = 0.0;
	sphere2.color.r = 123;
	sphere2.color.g = 173;
	sphere2.color.b = 0;

	t_cylinder	cylinder;
	cylinder.radius = 0.3;
	cylinder.pos = init_vector(1.0, 0.5, 0.0);
	cylinder.length = 5.0;
	cylinder.color.r = 0;
	cylinder.color.r = 123;
	cylinder.color.r = 173;

	t_plane	   ground;
	ground.pos.x = 0.0;
	ground.pos.y = 1.0;
	ground.pos.z = 0.0;
	ground.normal.x = 0.0;
	ground.normal.y = 1.0;
	ground.normal.z = 0.0;
	ground.color.r = 123;
	ground.color.g = 123;
	ground.color.b = 123;

	t_light		light;
	light.pos.x	= 0.0;
	light.pos.y	= -1.0;
	light.pos.z	= -3.0;
	light.color.r = 255;
	light.color.g = 255;
	light.color.b = 255;

	t_node		*node;
	t_scene		scene;
	t_coord		drawn_pixel;

	scene = init_scene(WIDTH, HEIGHT);
	node = init_node(SPHERE, &sphere2, "sphere 2");
	node_add(&(scene.objects), node);
	node = init_node(CYLINDER, &cylinder, "cylinder");
	node_add(&(scene.objects), node);
	node = init_node(PLANE, &ground, "ground");
	node_add(&(scene.objects), node);

	node = init_node(LIGHT, &light, "light 1");
	node_add(&(scene.lights), node);

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			cam.ray.dir = calc_vec_dir(x, y, cam, look);
			drawn_pixel = find_closest_object(scene.objects, cam.ray);
			drawn_pixel = apply_light(scene, drawn_pixel, cam.ray);
			put_pixel_on_image(env->img, x, y, drawn_pixel.color);
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
