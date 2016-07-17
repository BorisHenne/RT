/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/17 04:05:52 by nbelouni         ###   ########.fr       */
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
	sphere2.radius = 0.2;
	sphere2.center.x = 0.5;
	sphere2.center.y = 0.8;
	sphere2.center.z = 0.0;
	sphere2.color.r = 0;
	sphere2.color.g = 223;
	sphere2.color.b = 223;

	t_sphere	sphere3;
	sphere3.radius = 0.3;
	sphere3.center.x = 0.0;
	sphere3.center.y = 0.7;
	sphere3.center.z = 0.0;
	sphere3.color.r = 255;
	sphere3.color.g = 255;
	sphere3.color.b = 0;

	t_sphere	sphere4;
	sphere4.radius = 0.2;
	sphere4.center.x = -0.2;
	sphere4.center.y = 0.8;
	sphere4.center.z = -0.4;
	sphere4.color.r = 255;
	sphere4.color.g = 78;
	sphere4.color.b = 123;

	t_cylinder	cylinder;
	cylinder.radius = 0.3;
	cylinder.pos = init_vector(1.0, 0.0, 0.0);
	cylinder.length = 5.0;
	cylinder.color.r = 255;
	cylinder.color.g = 255;
	cylinder.color.b = 255;

	t_cone		cone;
	cone.ang = deg_to_rad(25);
	cone.pos = init_vector(0.0, -1.0, 1.0);
	cone.len = 0.8;
	cone.color.r = 173;
	cone.color.g = 0;
	cone.color.b = 123;

	t_plane	   ground;
	ground.pos.x = 0.0;
	ground.pos.y = 1.0;
	ground.pos.z = 0.0;
	ground.normal.x = 0.0;
	ground.normal.y = 1.0;
	ground.normal.z = 0.0;
	ground.color.r = 255;
	ground.color.g = 255;
	ground.color.b = 255;

	t_light		light;
	light.pos.x = -5.0;
	light.pos.y = -5.0;
	light.pos.z = 0.0;
	light.color.r = 255;
	light.color.g = 255;
	light.color.b = 255;

	t_light		light2;
	light2.pos.x = 5.0;
	light2.pos.y = -5.0;
	light2.pos.z = 0.0;
	light2.color.r = 255;
	light2.color.g = 255;
	light2.color.b = 255;

	t_light		light3;
	light3.pos.x = 0.0;
	light3.pos.y = 0.0;
	light3.pos.z = -5.0;
	light3.color.r = 255;
	light3.color.g = 255;
	light3.color.b = 255;

	t_light		light4;
	light4.pos.x = 0.0;
	light4.pos.y = -5.0;
	light4.pos.z = 0.0;
	light4.color.r = 255;
	light4.color.g = 255;
	light4.color.b = 255;


	t_node		*node;
	t_scene		scene;
	t_coord		drawn_pixel;

	scene = init_scene(WIDTH, HEIGHT);

	node = init_node(SPHERE, &sphere2, "sphere 1 couleur", 1);
	node_add(&(scene.objects), node);
	node = init_node(SPHERE, &sphere3, "sphere 2 couleurs", 2);
	node_add(&(scene.objects), node);
	node = init_node(SPHERE, &sphere4, "sphere 3 couleurs", 3);
	node_add(&(scene.objects), node);
//	node = init_node(CYLINDER, &cylinder, "cylinder", 4);
//	node_add(&(scene.objects), node);
//	node = init_node(CONE, &cone, "cone", 5);
//	node_add(&(scene.objects), node);
	node = init_node(PLANE, &ground, "ground", 6);
	node_add(&(scene.objects), node);

	node = init_node(LIGHT, &light, "light 1", 1);
	node_add(&(scene.lights), node);
	node = init_node(LIGHT, &light2, "light 2", 2);
	node_add(&(scene.lights), node);
//	node = init_node(LIGHT, &light3, "light 3", 3);
//	node_add(&(scene.lights), node);
	node = init_node(LIGHT, &light4, "light 4", 4);
	node_add(&(scene.lights), node);

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			cam.ray.dir = calc_vec_dir(x, y, cam, look);
			drawn_pixel = find_closest_object(scene.objects, cam.ray);
			if (drawn_pixel.bool == 1)
				drawn_pixel = apply_light(scene, drawn_pixel, cam.ray);
			put_pixel_on_image(env->img, x, y, drawn_pixel.color);
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
