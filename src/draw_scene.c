/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/14 03:36:00 by nbelouni         ###   ########.fr       */
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
	ori.z = -8.0;
	t_vec look;
	//	look = rotation avec valeur a mettre en radian pour le moment;
	look.x = deg_to_rad(0);
	look.y = deg_to_rad(0);
	look.z = deg_to_rad(0);
	t_vec init_vec;
	init_vec.x = 0.0;
	init_vec.y = 1.0;
	init_vec.z = 0.0;
	t_cam cam;

	cam = init_camera(ori);

//	t_sphere	sphere;
//	sphere.radius = 1.0;
//	sphere.center.x = -0.5;
//	sphere.center.y = -0.2;
//	sphere.center.z = 0.0;
//	sphere.color.r = 173;
//	sphere.color.g = 0;
//	sphere.color.b = 0;

	t_sphere	sphere2;
	sphere2.radius = 0.3;
	sphere2.center.x = 0.0;
	sphere2.center.y = 0.0;
	sphere2.center.z = 0.0;
	sphere2.color.r = 123;
	sphere2.color.g = 173;
	sphere2.color.b = 0;

//	t_cylinder	cylinder;
//	cylinder.radius = 0.4;
//	cylinder.pos.x = 0.0;
//	cylinder.pos.y = 0.0;
//	cylinder.pos.z = -1.0;
//	cylinder.length = 12.0;
//	cylinder.color.r = 0;
//	cylinder.color.g = 123;
//	cylinder.color.b = 0;

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

<<<<<<< HEAD
//	   t_plane	   ceil;
//	   ceil.pos.x = 0.0;
//	   ceil.pos.y = -1.0;
//	   ceil.pos.z = 0.0;
//	   ceil.normal.x = 0.0;
//	   ceil.normal.y = 1.0;
//	   ceil.normal.z = -0.0;
//	   ceil.color.r = 223;
//	   ceil.color.g = 223;
//	   ceil.color.b = 223;
//
//	   t_plane	   left_side;
//	   left_side.pos.x = 1.0;
//	   left_side.pos.y = 0.0;
//	   left_side.pos.z = 0.0;
//	   left_side.normal.x = 1.0;
//	   left_side.normal.y = 0.0;
//	   left_side.normal.z = 0.0;
//	   left_side.color.r = 177;
//	   left_side.color.g = 177;
//	   left_side.color.b = 177;
//
//	   t_plane	   right_side;
//	   right_side.pos.x = -1.0;
//	   right_side.pos.y = 0.0;
//	   right_side.pos.z = 0.0;
//	   right_side.normal.x = -1.0;
//	   right_side.normal.y = 0.0;
//	   right_side.normal.z = 0.0;
//	   right_side.color.r = 177;
//	   right_side.color.g = 177;
//	   right_side.color.b = 177;
//
//	   t_plane	   back_side;
//	   back_side.pos.x = 0.0;
//	   back_side.pos.y = 0.0;
//	   back_side.pos.z = 25.0;
//	   back_side.normal.x = 0.0;
//	   back_side.normal.y = 0.0;
//	   back_side.normal.z = 1.0;
//	   back_side.color.r = 0;
//	   back_side.color.g = 0;
//	   back_side.color.b = 0;
//
=======
	   t_plane	   ceil;
	   ceil.pos.x = 0.0;
	   ceil.pos.y = -1.0;
	   ceil.pos.z = 0.0;
	   ceil.normal.x = 0.0;
	   ceil.normal.y = 1.0;
	   ceil.normal.z = -0.0;
	   ceil.color.r = 223;
	   ceil.color.g = 223;
	   ceil.color.b = 223;

	   t_plane	   left_side;
	   left_side.pos.x = 1.0;
	   left_side.pos.y = 0.0;
	   left_side.pos.z = 0.0;
	   left_side.normal.x = 1.0;
	   left_side.normal.y = 0.0;
	   left_side.normal.z = 0.0;
	   left_side.color.r = 177;
	   left_side.color.g = 177;
	   left_side.color.b = 177;

	   t_plane	   right_side;
	   right_side.pos.x = -1.0;
	   right_side.pos.y = 0.0;
	   right_side.pos.z = 0.0;
	   right_side.normal.x = -1.0;
	   right_side.normal.y = 0.0;
	   right_side.normal.z = 0.0;
	   right_side.color.r = 177;
	   right_side.color.g = 177;
	   right_side.color.b = 177;

	   t_plane	   back_side;
	   back_side.pos.x = 0.0;
	   back_side.pos.y = 0.0;
	   back_side.pos.z = 25.0;
	   back_side.normal.x = 0.0;
	   back_side.normal.y = 0.0;
	   back_side.normal.z = 1.0;
	   back_side.color.r = 0;
	   back_side.color.g = 0;
	   back_side.color.b = 0;

	   t_cone	cone;
	   cone.pos = init_vector(5.0f, -5.0f, 10.0f);
	   cone.dir = init_vector(0.0f, 0.0f, 0.0f);
	   cone.len = 1.0f;
	   cone.ang = 0.785398;
	   cone.color.r = 255;
	   cone.color.g = 0;
	   cone.color.b = 255;

	t_node		*node;
	t_scene		scene;
	t_coord		drawn_pixel;
	
	scene = init_scene(WIDTH, HEIGHT);
//	node = init_node(SPHERE, &sphere, "sphere 1");
//	node_add(&(scene.objects), node);
	node = init_node(SPHERE, &sphere2, "sphere 2");
	node_add(&(scene.objects), node);
//	node = init_node(CYLINDER, &cylinder, "cylinder 1");
//	node_add(&(scene.objects), node);
	node = init_node(PLANE, &ground, "ground");
	node_add(&(scene.objects), node);
//	node = init_node(PLANE, &ceil, "ceil");
//	node_add(&(scene.objects), node);
//	node = init_node(PLANE, &left_side, "left_side");
//	node_add(&(scene.objects), node);
//	node = init_node(PLANE, &right_side, "right_side");
//	node_add(&(scene.objects), node);
//	node = init_node(PLANE, &back_side, "back_side");
//	node_add(&(scene.objects), node);

	t_light		light;

	light.pos.x	= 0.0;
	light.pos.y	= -5.0;
	light.pos.z	= -3.0;
	light.color.r = 255;
	light.color.g = 255;
	light.color.b = 255;

	node = init_node(LIGHT, &light, "light 1");
	node_add(&(scene.lights), node);

	node = init_node(CONE, &cone, "cone 1");
	node_add(&(scene.nodes), node);

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
