/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:41:15 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/14 01:08:32 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

void		write_scene(t_scene s);

void		write_vector(t_vec v, char *name)
{
	printf("\t\t- %s:\t%f %f %f\n", name, v.x, v.y, v.z);
}

void		write_camera(t_cam *c)
{
	write_vector(c->ray.pos, "pos");
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
