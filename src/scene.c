/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:41:15 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/24 18:53:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

void		write_scene(t_scene s);

void		write_vector(t_vec v, char *name)
{
	printf("\t\t- %s:\t%f %f %f\n", name, v.x, v.y, v.z);
}

void		print_camera(t_cam *c)
{
	write_vector(c->ray.pos, "pos");
	write_vector(c->ray.dir, "dir");
	write_vector(c->look_at, "look_at");
	printf("\t\t- w: %f\n", c->w);
	printf("\t\t- h: %f\n", c->h);
	printf("\t\t- d: %f\n", c->d);
}

t_scene		init_scene(int w, int h, int is_real)
{
	t_scene	s;

	s.is_real = is_real;
	s.w = w;
	s.h = h;
//	s.cam = NULL;
	s.objects = NULL;
	s.lights = NULL;
	return (s);
}


// paye ta fonction poto !
void		add_camera(t_scene *s, t_cam cam)
{
//	t_cam	new_cam;
//
////	new_cam = (t_cam *)malloc(sizeof(t_cam));
//	new_cam.ray.pos = cam.ray.pos;
//	new_cam.ray.dir = cam.ray.dir;
//	new_cam.look_at = cam.look_at;
//	new_cam.w = cam.w;
//	new_cam.h = cam.h;
//	new_cam.d = cam.d;
	s->cam = cam;
}

void		write_scene(t_scene s)
{
	t_node	*tmp;

	printf("SCENE [%dx%d]\n", s.w, s.h);
	printf("\tCAMERA:\n");
//	if (s.cam == NULL)
//	{ 
//		printf("\t\t- NULL\n");
//	}
//	else
//	{
		print_camera(&(s.cam));
//	}
	printf("\tNODES:\n ");
	if (s.objects == NULL)
	{
		printf("\t\t- NULL\n");
	}
	else
	{
		tmp = s.objects;
		while (tmp != NULL)
		{
			printf("\t\t- coucou %s\n", tmp->name);
			tmp = tmp->next;
		}
	}
	if (s.lights == NULL)
	{
		printf("\t\t- NULL\n");
	}
	else
	{
		tmp = s.lights;
		while (tmp != NULL)
		{
			printf("\t\t- coucou %s\n", tmp->name);
			tmp = tmp->next;
		}
	}
}
