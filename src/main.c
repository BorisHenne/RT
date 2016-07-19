/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/17 22:36:21 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "rtv1.h"

#include <stdio.h>
//int		expose_hook(t_env *e)
//{
//	RAYTRACER
//}

void		write_scene(t_scene s);
t_scene		init_all(void)
{
	t_vec ori;
	ori.x = 0.0;
	ori.y = 0.0;
	ori.z = -10.0;
	t_vec look;
	look.x = deg_to_rad(0);
	look.y = deg_to_rad(0);
	look.z = deg_to_rad(0);
	t_cam cam;

	cam = init_camera(ori, look);

	t_sphere	*sphere2;
	sphere2 = (t_sphere *)malloc(sizeof(t_sphere));
	sphere2->radius = 0.5;
	sphere2->center.x = 0.0;
	sphere2->center.y = 0.0;
	sphere2->center.z = 0.0;
	sphere2->color.r = 0;
	sphere2->color.g = 223;
	sphere2->color.b = 223;

	t_sphere	*sphere3;
	sphere3 = (t_sphere *)malloc(sizeof(t_sphere));
	sphere3->radius = 0.3;
	sphere3->center.x = 0.0;
	sphere3->center.y = 0.7;
	sphere3->center.z = 0.0;
	sphere3->color.r = 255;
	sphere3->color.g = 255;
	sphere3->color.b = 0;

	t_sphere	*sphere4;
	sphere4 = (t_sphere *)malloc(sizeof(t_sphere));
	sphere4->radius = 0.2;
	sphere4->center.x = -0.2;
	sphere4->center.y = 0.8;
	sphere4->center.z = -0.4;
	sphere4->color.r = 255;
	sphere4->color.g = 78;
	sphere4->color.b = 123;

	t_cylinder	*cylinder;
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->radius = 0.3;
	cylinder->pos = init_vector(1.0, 0.0, 0.0);
	cylinder->length = 5.0;
	cylinder->color.r = 255;
	cylinder->color.g = 255;
	cylinder->color.b = 255;

	t_cone		*cone;
	cone = (t_cone *)malloc(sizeof(t_cone));
	cone->ang = deg_to_rad(25);
	cone->pos = init_vector(0.0, -1.0, 1.0);
	cone->len = 0.8;
	cone->color.r = 173;
	cone->color.g = 0;
	cone->color.b = 123;

	t_plane	   *ground;
	ground = (t_plane *)malloc(sizeof(t_plane));
	ground->pos.x = 0.0;
	ground->pos.y = 1.0;
	ground->pos.z = 0.0;
	ground->normal.x = 0.0;
	ground->normal.y = 1.0;
	ground->normal.z = 0.0;
	ground->color.r = 255;
	ground->color.g = 255;
	ground->color.b = 255;

	t_light		*light;
	light = (t_light *)malloc(sizeof(t_light));
	light->pos.x = -5.0;
	light->pos.y = -5.0;
	light->pos.z = 0.0;
	light->color.r = 255;
	light->color.g = 255;
	light->color.b = 255;

	t_light		*light2;
	light2 = (t_light *)malloc(sizeof(t_light));
	light2->pos.x = 5.0;
	light2->pos.y = -5.0;
	light2->pos.z = 0.0;
	light2->color.r = 255;
	light2->color.g = 255;
	light2->color.b = 255;

	t_light		*light3;
	light3 = (t_light *)malloc(sizeof(t_light));
	light3->pos.x = 0.0;
	light3->pos.y = 0.0;
	light3->pos.z = -5.0;
	light3->color.r = 255;
	light3->color.g = 255;
	light3->color.b = 255;

	t_light		*light4;
	light4 = (t_light *)malloc(sizeof(t_light));
	light4->pos.x = 0.0;
	light4->pos.y = -5.0;
	light4->pos.z = 0.0;
	light4->color.r = 255;
	light4->color.g = 255;
	light4->color.b = 255;


	t_node		*node;
	t_scene		scene;

	scene = init_scene(WIDTH, HEIGHT);
	add_camera(&scene, cam);

	node = init_node(SPHERE, sphere2, "sphere2", 1);
	node_add(&(scene.objects), node);
	node = init_node(SPHERE, sphere3, "sphere 2 couleurs", 2);
	node_add(&(scene.objects), node);
	node = init_node(SPHERE, sphere4, "sphere 3 couleurs", 3);
	node_add(&(scene.objects), node);
	node = init_node(CYLINDER, cylinder, "cylinder", 4);
	node_add(&(scene.objects), node);
	node = init_node(CONE, cone, "cone", 5);
	node_add(&(scene.objects), node);
	node = init_node(PLANE, ground, "ground", 6);
	node_add(&(scene.objects), node);

	node = init_node(LIGHT, light, "light 1", 1);
	node_add(&(scene.lights), node);
	node = init_node(LIGHT, light2, "light 2", 2);
	node_add(&(scene.lights), node);
	node = init_node(LIGHT, light3, "light 3", 3);
	node_add(&(scene.lights), node);
	node = init_node(LIGHT, light4, "light 4", 4);
	node_add(&(scene.lights), node);

	return (scene);
}

int	main(int ac, char** av)
{
	t_env	e;
	t_scene	scene;
	e.mlx = mlx_init();
	if (e.mlx != NULL)
	{
		e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "RTv1");
		if (!(e.img = mlx_new_image(e.mlx, WIDTH, HEIGHT)))
			return (0);
		scene = init_all();
		draw_scene(&e, scene);
		mlx_hook(e.win, 2, 3, key_hook, &e);
//		mlx_expose_hook(e.win, expose_hook, &e);
		mlx_loop(e.mlx);
	}
	free_node_list(&(scene.objects));
	free_node_list(&(scene.lights));
	(void)ac;
	(void)av;
	return (0);
}
