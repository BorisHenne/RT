/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/06 07:24:29 by tlepeche         ###   ########.fr       */
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
	ori.x = 0;
	ori.y = -20;
	ori.z = -20;
	t_vec look;
	look.x = deg_to_rad(-45);
	look.y = deg_to_rad(0);
	look.z = deg_to_rad(0);
	t_cam cam;

	cam = init_camera(ori, look);

	t_elips	*elips;
	elips = (t_elips *)malloc(sizeof(t_elips));
	elips->center = init_vector(1, 0.5, 4);
	elips->radius = 0.3;
	elips->quad.A = 0.3;
	elips->quad.B = 1;
	elips->quad.C = 1;
	elips->color.r = 1;
	elips->color.g = 1;
	elips->color.b = 0;
	elips->specular = 90;
	elips->reflection = 0;
	elips->opacity = 1;
	elips->ref_index = 1;
	elips->texture = NONE;
	elips->is_negativ = 0;

	t_sphere	*sphere2;
	sphere2 = (t_sphere *)malloc(sizeof(t_sphere));
	sphere2->radius = 0.3;
	sphere2->center = init_vector(-0.3, .5, 2.0);
	sphere2->color.r = 0.1;
	sphere2->color.g = 0.1;
	sphere2->color.b = 0.1;
	sphere2->specular = 90;
	sphere2->reflection = 1;
	sphere2->opacity = 1;
	sphere2->ref_index = 1;
	sphere2->texture = NONE;
	sphere2->is_negativ = 0;
	
	t_sphere	*sphere3;
	sphere3 = (t_sphere *)malloc(sizeof(t_sphere));
	sphere3->radius = 0.3;
	sphere3->center = init_vector(-.3, -.1, 4.0);
	sphere3->color.r = 0.8;
	sphere3->color.g = 0.1;
	sphere3->color.b = 0.1;
	sphere3->specular = 90;
	sphere3->reflection = 0;
	sphere3->opacity = 1;
	sphere3->ref_index = 1;
	sphere3->texture = MARBLE;
	sphere3->is_negativ = 0;

	t_sphere	*sphere4;
	sphere4 = (t_sphere *)malloc(sizeof(t_sphere));
	sphere4->radius = 0.3;
	sphere4->center = init_vector(-1, 0.5, 6.0);
	sphere4->color.r = 0.1;
	sphere4->color.g = 0.2;
	sphere4->color.b = 1;
	sphere4->specular = 50;
	sphere4->reflection = 0;
	sphere4->opacity = 1;
	sphere4->ref_index = 1;
	sphere4->texture = MARBLE;
	sphere4->is_negativ = 0;

	t_cylinder	*cylinder;
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->radius = 0.3;
	//cylinder->pos = init_vector(0.2, 0, 2.0);
	//cylinder->dir = init_vector(0.8, 0.5, -0.3);
	cylinder->pos = init_vector(2, 0, 2.0);
	cylinder->dir = init_vector(0.1, 0.5, -0.3);
	cylinder->length = 2;
	cylinder->color.r = 0.1;
	cylinder->color.g = 1;
	cylinder->color.b = 0.1;
	cylinder->specular = 100;
	cylinder->reflection = 0;
	cylinder->opacity = 0.4;
	cylinder->ref_index = 1;
	cylinder->texture = MARBLE;
	cylinder->is_negativ = 0;

	t_cone	*cone;
	cone = (t_cone *)malloc(sizeof(t_cone));
	cone->r = 0.5;
	cone->pos = init_vector(0.2, 0, 2.0);
	cone->dir = init_vector(0.8, 0.5, -0.3);
//	cone->pos = init_vector(2, 0, 2.0);
//	cone->dir = init_vector(0.1, 0.5, -0.3);
	cone->len = 1;
	cone->color.r = 1;
	cone->color.g = 0.4;
	cone->color.b = 0.4;
	cone->specular = 50;
	cone->reflection = 0;
	cone->opacity = 0.6;
	cone->ref_index = 1.33;
	cone->texture = NONE;
	cone->is_negativ = 0;

	t_plane	   *ground;
	ground = (t_plane *)malloc(sizeof(t_plane));
	ground->pos = init_vector(-1.0, 1.0, 0.0);
	ground->normal = init_vector(0., 1.2, 0.0);
	ground->color.r = 0.3;
	ground->color.g = 0.3;
	ground->color.b = 0.3;
	ground->specular = 100;
	ground->reflection = 1;
	ground->opacity = 1;
	ground->ref_index = 1.0;
	ground->texture = CHECKER;
	ground->is_negativ = 0;

	t_light		*light;
	light = (t_light *)malloc(sizeof(t_light));
	light->type = DIRECT;
	light->pos = init_vector(0., -5, -4.);
	light->color = init_color(255, 255, 255);
	light->look_at = init_vector(0, 0, 0);
	light->angle = deg_to_rad(360);

	t_light		*light2;
	light2 = (t_light *)malloc(sizeof(t_light));
	light2->type = DIRECT;
	light2->pos = init_vector(0.6, -1.4, -1.6);
	light2->color = init_color(0, 0, 255);
	light2->look_at = init_vector(0, 0, 0);
	light2->angle = deg_to_rad(30);

	t_node		*node;
	t_scene		scene;

//	scene = init_scene(WIDTH, HEIGHT, CARTOON);
	scene = init_scene(WIDTH, HEIGHT, REALISTIC);
	add_camera(&scene, cam);

	node = init_node(ELIPS, elips, "elipsoid", 8);
	node_add(&(scene.objects), node);
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
//	node = init_node(CONE, cone2, "cone2", 7);
//	node_add(&(scene.objects), node);
	node = init_node(PLANE, ground, "ground", 6);
	node_add(&(scene.objects), node);
//	node = init_node(PLANE, ceil, "ceil", 7);
//	node_add(&(scene.objects), node);

	node = init_node(LIGHT, light, "light 1", 1);
	node_add(&(scene.lights), node);
	node = init_node(LIGHT, light2, "light 2", 2);
	node_add(&(scene.lights), node);
//	node = init_node(LIGHT, light3, "light 3", 3);
//	node_add(&(scene.lights), node);
//	node = init_node(LIGHT, light4, "light 4", 4);
//	node_add(&(scene.lights), node);

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
