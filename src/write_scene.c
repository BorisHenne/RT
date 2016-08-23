/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 19:08:18 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/22 19:10:29 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>
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


void		write_light(t_light	*light)
{
	printf("\t\t- type : %d\n", light->type);
	write_vector(light->pos, "pos");
	write_vector(light->look_at, "look_at");
	printf("\t\t- color : %f, %f, %f\n", light->color.r, light->color.g, light->color.b);
	printf("\t\t- angle : %f\n", light->angle);
}

void		write_sphere(t_sphere *s)
{
	printf("\t\t- radius : %f\n", s->radius);
	write_vector(s->center, "center");
	printf("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	printf("\t\t- specular : %d\n", s->specular);
	printf("\t\t- reflection : %f\n", s->reflection);
	printf("\t\t- opacity : %f\n", s->opacity);
	printf("\t\t- ref_index : %f\n", s->ref_index);
	printf("\t\t- is_negativ : %d\n", s->is_negativ);
	printf("\t\t- texture : %d\n", s->texture);
}

void		write_elips(t_elips *s)
{
	printf("\t\t- radius : %f\n", s->radius);
	write_vector(s->center, "center");
	printf("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	printf("\t\t- specular : %d\n", s->specular);
	printf("\t\t- reflection : %f\n", s->reflection);
	printf("\t\t- opacity : %f\n", s->opacity);
	printf("\t\t- ref_index : %f\n", s->ref_index);
	printf("\t\t- is_negativ : %d\n", s->is_negativ);
	printf("\t\t- texture : %d\n", s->texture);
}

void		write_plane(t_plane *s)
{
	write_vector(s->pos, "pos");
	write_vector(s->normal, "normal");
	printf("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	printf("\t\t- specular : %d\n", s->specular);
	printf("\t\t- reflection : %f\n", s->reflection);
	printf("\t\t- opacity : %f\n", s->opacity);
	printf("\t\t- ref_index : %f\n", s->ref_index);
	printf("\t\t- is_negativ : %d\n", s->is_negativ);
	printf("\t\t- texture : %d\n", s->texture);
}

void		write_cylinder(t_cylinder *s)
{
	printf("\t\t- radius : %f\n", s->radius);
	write_vector(s->pos, "pos");
	write_vector(s->dir, "dir");
	printf("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	printf("\t\t- length : %f\n", s->length);
	printf("\t\t- h : %f\n", s->h);
	printf("\t\t- specular : %d\n", s->specular);
	printf("\t\t- reflection : %f\n", s->reflection);
	printf("\t\t- opacity : %f\n", s->opacity);
	printf("\t\t- ref_index : %f\n", s->ref_index);
	printf("\t\t- is_negativ : %d\n", s->is_negativ);
	printf("\t\t- texture : %d\n", s->texture);
}

void		write_cone(t_cone *s)
{
	printf("\t\t- radius : %f\n", s->r);
	write_vector(s->pos, "pos");
	write_vector(s->dir, "dir");
	printf("\t\t- color : %f, %f, %f\n", s->color.r, s->color.g, s->color.b);
	printf("\t\t- length : %f\n", s->len);
	printf("\t\t- specular : %d\n", s->specular);
	printf("\t\t- reflection : %f\n", s->reflection);
	printf("\t\t- opacity : %f\n", s->opacity);
	printf("\t\t- ref_index : %f\n", s->ref_index);
	printf("\t\t- is_negativ : %d\n", s->is_negativ);
	printf("\t\t- texture : %d\n", s->texture);
}

void		write_scene(t_scene s)
{
	t_node	*tmp;

	printf("SCENE [%dx%d]\n", s.w, s.h);
	printf(" - cartoon : %d\n\n", s.is_real);
	printf("\tCAMERA:\n");
	print_camera(&(s.cam));
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
			printf("\t%s :\n", tmp->name);
			if (tmp->type == SPHERE)
				write_sphere((t_sphere *)(tmp->data));
			if (tmp->type == CYLINDER)
				write_cylinder((t_cylinder *)(tmp->data));
			if (tmp->type == PLANE)
				write_plane((t_plane *)(tmp->data));
			if (tmp->type == CONE)
				write_cone((t_cone *)(tmp->data));
			if (tmp->type == ELIPS)
				write_elips((t_elips *)(tmp->data));
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
			printf("\t- %s :\n", tmp->name);
			write_light((t_light *)(tmp->data));
			tmp = tmp->next;
		}
	}
}
