/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:50:11 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/13 05:19:43 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

#define CAMERA		1
#define SPHERE		2
#define CYLINDER	3

t_node		*init_node(int type, void *data, char *name)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->type = type;
	node->data = data;
	node->name = name;
	node->next = NULL;
	return (node);
}

void		node_add(t_node **node, t_node	*new)
{
	new->next = *(node);
	*node = new;
}
/*
int			main(void)
{
	t_node		*node;
	t_node		*node2;
	t_node		*node3;
	t_node		*tmp;
	t_sphere	sphere;
	t_sphere	sphere2;
	t_cylinder	cylinder;
	t_vec		center;
	t_vec		center2;
	t_vec		center3;

	// vector
	center = init_vector(0.0f, 0.0f, 0.0f);
	center2 = init_vector(1.0f, 1.0f, 1.0f);
	center3 = init_vector(3.0f, 3.0f, 3.0f);
	// sphere
	sphere.radius = 2.0f;
	sphere.center = center;
	sphere2.radius = 1.0f;
	sphere2.center = center2;
	// cylinder
	cylinder. radius = 5.0f;
	cylinder.start_point = center3;
	cylinder.dir = center;
	cylinder.lenght = 12.0f;

	// node
	node = init_node(SPHERE, &sphere);
	node2 = init_node(SPHERE, &sphere2);
	node3 = init_node(CYLINDER, &cylinder);
	node_add(&node, node2);
	node_add(&node, node3);	
	// TEST
	tmp = node;
	while (tmp != NULL)
	{
		t_sphere	*s;
		t_cylinder	*c;

		printf("type: %d\n", tmp->type);
		if (tmp->type == SPHERE)
		{
			s = (t_sphere *)(tmp->data);
			printf("Hey la sphere\n");
			printf("radius: %f\n", s->radius);
			printf("center: x: %f\t%f\t%f\n", s->center.x, s->center.y, s->center.z);
		}
		else if (tmp->type == CYLINDER)
		{
			c = (t_cylinder *)(tmp->data);
			printf("Hey le cylindre\n");
			printf("radius: %f\n", c->radius);
			printf("center: x: %f\t%f\t%f\n", c->start_point.x, c->start_point.y, c->start_point.z);
		}
		tmp = tmp->next;
	}
	return (0);
}
*/
