/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/13 06:11:16 by tlepeche         ###   ########.fr       */
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

	t_sphere	sphere;
	sphere.radius = 1.0;
	sphere.center.x = 0.0;
	sphere.center.y = 0.0;
	sphere.center.z = 0.0;
	sphere.color.r = 123;
	sphere.color.g = 0;
	sphere.color.b = 0;


	t_cylinder	cylinder;
	cylinder.radius = 0.2;
	cylinder.pos.x = 0.0;
	cylinder.pos.y = -0.8;
	cylinder.pos.z = 5.0;
//	cylinder.rot.x = 1.0;
//	cylinder.rot.y = 1.0;
//	cylinder.rot.z = 1.0;
	cylinder.length = 2.0;
	cylinder.color.r = 0;
	cylinder.color.g = 123;
	cylinder.color.b = 0;

	   t_plane	   plan1;
	   plan1.pos.x = 0.0;
	   plan1.pos.y = 0.0;
	   plan1.pos.z = 0.0;
	   plan1.normal.x = 0.0;
	   plan1.normal.y = 1.0;
	   plan1.normal.z = 0.1;
	   plan1.color.r = 223;
	   plan1.color.g = 123;
	   plan1.color.b = 0;
/*
	   t_plane	   plan2;
	   plan2.pos.x = 100.0;
	   plan2.pos.y = 0.0;
	   plan2.pos.z = 0.0;
	   plan2.normal.x = -1.0;
	   plan2.normal.y = 0.0;
	   plan2.normal.z = 0.0;
	   plan2.color.r = 223;
	   plan2.color.g = 123;
	   plan2.color.b = 0;
*/
	t_node		*node;
	t_scene		scene;
	t_coord		drawn_pixel;
	
	scene = init_scene(WIDTH, HEIGHT);
	node = init_node(SPHERE, &sphere, "sphere 1");
	node_add(&(scene.nodes), node);
	node = init_node(CYLINDER, &cylinder, "cylinder 1");
	node_add(&(scene.nodes), node);
	node = init_node(PLANE, &plan1, "plan 1");
	node_add(&(scene.nodes), node);
/*
	node = init_node(PLANE, &plan2, "plan 2");
	node_add(&(scene.nodes), node);
*/	
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			cam.dir = calc_vec_dir(x, y, cam, look);
			drawn_pixel = find_closest_object(scene.nodes, cam);
			put_pixel_on_image(env->img, x, y, drawn_pixel.color);
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
