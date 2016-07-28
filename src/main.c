/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/28 18:10:08 by tlepeche         ###   ########.fr       */
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
	sphere2->radius = 0.3;
	sphere2->center = init_vector(1.0, 0.0, 0.0);
	sphere2->color.r = 0.3;
	sphere2->color.g = 0.3;
	sphere2->color.b = 0.3;
	sphere2->specular = 90;
	sphere2->reflection = 0;
	sphere2->opacity = 1;
	sphere2->ref_index = 1.5;
	sphere2->texture = MARBLE;
	sphere2->is_negativ = 0;
	
	/*	t_sphere	*sphere3;
	sphere3 = (t_sphere *)malloc(sizeof(t_sphere));
	sphere3->radius = 0.3;
	sphere3->center = init_vector(1.0, 0., 0.0);
	sphere3->color.r = 1;
	sphere3->color.g = 1;
	sphere3->color.b = 0.4;
	sphere3->specular = 50;
	sphere3->reflection = 0;
	sphere3->opacity = 0.9;
	sphere3->ref_index = 2.5;
	sphere3->texture = NONE;
	sphere3->is_negativ = 0;

	t_sphere	*sphere4;
	sphere4 = (t_sphere *)malloc(sizeof(t_sphere));
	sphere4->radius = 0.3;
	sphere4->center = init_vector(-1.0, 0.0, 0.0);
	sphere4->color.r = 1;
	sphere4->color.g = 0.4;
	sphere4->color.b = 0.4;
	sphere4->specular = 50;
	sphere4->reflection = 0;
	sphere4->opacity = 0.5;
	sphere4->ref_index = 3.5;
	sphere4->texture = WOOD;
	sphere4->is_negativ = 0;

*/	t_cylinder	*cylinder;
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->radius = 0.2;
	cylinder->pos = init_vector(1, 0.0, 0.0);
	cylinder->dir = init_vector(0, 1, 0.);
	cylinder->length = 1;
	cylinder->color.r = 1;
	cylinder->color.g = 0.;
	cylinder->color.b = 0.8;
	cylinder->specular = 50;
	cylinder->reflection = 0;
	cylinder->opacity = 1;
	cylinder->ref_index = 1;
	cylinder->texture = NONE;
	cylinder->is_negativ = 0;

	t_cone		*cone;
	cone = (t_cone *)malloc(sizeof(t_cone));
	cone->pos = init_vector(-1, 0, 0.0);
	cone->dir = init_vector(1, 0.5, 0.8);
	cone->len = 1;
	cone->r = 0.5;//*deg_to_rad(20);
	cone->color.r = 1;
	cone->color.g = 0;
	cone->color.b = 0.8;
	cone->specular = 20;
	cone->reflection = 0;
	cone->opacity = 1;
	cone->texture = NONE;
	cone->is_negativ = 0;
	cone->ref_index = 1.0;

	t_plane	   *ground;
	ground = (t_plane *)malloc(sizeof(t_plane));
	ground->pos = init_vector(0.0, 1.0, 0.0);
	ground->normal = init_vector(0.0, 1.2, 0.0);
	ground->color.r = 0.8;
	ground->color.g = 0.8;
	ground->color.b = 0.8;
	ground->specular = 100;
	ground->reflection = 0;
	ground->opacity = 1;
	ground->ref_index = 1.0;
	ground->texture = NONE;
	ground->is_negativ = 0;

	t_light		*light;
	light = (t_light *)malloc(sizeof(t_light));
	light->type = DIRECT;
	light->pos = init_vector(0.6, -1.4, -1.6);
	light->color = init_color(255, 255, 255);
	light->look_at = init_vector(-1, 0, 1);
	light->angle = deg_to_rad(360);

/*	t_light		*light2;
	light2 = (t_light *)malloc(sizeof(t_light));
	light2->type = PARALLEL;
	light2->pos = init_vector(0.0, 1.0, 0.0);
	light2->color = init_color(255, 255, 255);
	light2->look_at = init_vector(0, 0, 0);
	light2->angle = deg_to_rad(0);

	t_light		*light3;
	light3 = (t_light *)malloc(sizeof(t_light));
	light3->type = DIFFUSE;
	light3->pos = init_vector(-5.0, -5.0, 0.0);
	light3->color = init_color(255, 188, 34);
	light3->look_at = init_vector(0, 0, 0);
	light3->angle = deg_to_rad(0);

	t_light		*light4;
	light4 = (t_light *)malloc(sizeof(t_light));
	light4->type = DIFFUSE;
	light4->pos = init_vector(5.0, -5.0, 0.0);
	light4->color = init_color(255, 255, 255);
	light4->look_at = init_vector(0, 0, 0);
	light4->angle = deg_to_rad(180);*/


	t_node		*node;
	t_scene		scene;

//	scene = init_scene(WIDTH, HEIGHT, CARTOON);
	scene = init_scene(WIDTH, HEIGHT, REALISTIC);
	add_camera(&scene, cam);

	node = init_node(SPHERE, sphere2, "sphere2", 1);
//	node_add(&(scene.objects), node);
/*	node = init_node(SPHERE, sphere3, "sphere 2 couleurs", 2);
	node_add(&(scene.objects), node);
	node = init_node(SPHERE, sphere4, "sphere 3 couleurs", 3);
	node_add(&(scene.objects), node);
*/	node = init_node(CYLINDER, cylinder, "cylinder", 4);
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
//	node = init_node(LIGHT, light2, "light 2", 2);
//	node_add(&(scene.lights), node);
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
