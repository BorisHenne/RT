/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:41:15 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/10 03:36:15 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>
#include <node.h>

void		write_scene(t_scene s);

void		write_vector(t_vec v, char *name)
{
	printf("\t\t- %s:\t%f %f %f\n", name, v.x, v.y, v.z);
}

void		write_camera(t_cam *c)
{
	write_vector(c->pos, "pos");
	write_vector(c->ver, "up");
}

t_scene		init_scene(int w, int h)
{
	t_scene	s;

	s.w = w;
	s.h = h;
	s.cam = NULL;
	s.nodes = NULL;
	return (s);
}


// paye ta fonction poto !
void		add_camera(t_scene *s, t_cam *cam)
{
	s->cam = cam;
}

int		main(void)
{
	t_scene	scene;
	t_cam		cam;
	t_node		*node;
	t_node		*tmp;
	t_sphere	s1;
	t_sphere	s2;
	//t_sphere	s3;
	t_cylinder	c1;
	//t_cylinder	c2;
	t_vec	pos;
	t_vec	up;
	t_vec	look;

	// creation de la scene
	scene = init_scene(640, 480);

	// creation de la camera
	pos = init_vector(0.0f, 0.0f, -5.0f);
	up = init_vector(0.0f, 0.0f, 0.0f);
	look = init_vector(0.0f, 1.0f, 0.0f);
	cam = init_camera(pos, look, up);
	//write_scene(scene);
	
	// ajout de la camera a la scene
	add_camera(&scene, &cam);
	
	// creation des objets de la scene (sphere, cylinder, ...)
	pos = init_vector(0.0f, 0.0f, 0.0f);
	s1.center = pos;
	s1.radius = 2.0f;
	//
	pos = init_vector(3.0f, 3.0f, 3.0f);
	s2.center = pos;
	s2.radius = 2.0f;
	//
	pos = init_vector(0.0f, 0.0f, 0.0f);
	look = init_vector(1.0f, 1.0f, 0.0f);
	c1.pos = pos;
	//c1.dir = look;
	c1.radius = 2.0f;
	c1.length = 2.0f;

	// ajout des objets a la scene
	node = init_node(2, &s1, "sphere 1"); // REMPLACER LE 2 AVEC LE BON DEFINE
	node_add(&(scene.nodes), node);
	node = init_node(2, &s2, "sphere 2"); // PAREIL
	node_add(&(scene.nodes), node);
	node = init_node(3, &c1, "cylinder 1"); // EZ
	node_add(&(scene.nodes), node);
	
	// printf la scene
	write_scene(scene);
	return (0);
}

// SALE !!!
void		write_scene(t_scene s)
{
	t_node	*tmp;

	printf("SCENE [%dx%d]\n", s.w, s.h);
	printf("\tCAMERA:\n");
	if (s.cam == NULL)
	{ 
		printf("\t\t- NULL\n");
	}
	else
	{
		write_camera(s.cam);
	}
	printf("\tNODES:\n ");
	if (s.nodes == NULL)
	{
		printf("\t\t- NULL\n");
	}
	else
	{
		tmp = s.nodes;
		while (tmp != NULL)
		{
			printf("\t\t- coucou %s\n", tmp->name);
			tmp = tmp->next;
		}
	}
}
