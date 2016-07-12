/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:50:11 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/12 02:53:25 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

#define CAMERA 1
#define SPHERE 2

t_node		*init_node(int type, void *data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->type = type;
	node->data = data;
	node->next = NULL;
	return (node);
}

void		node_add(t_node **node, t_node	*new)
{
	new->next = *(node);
	*node = new;
}

int			main(void)
{
	t_node		*node;
	t_node		*node2;
	t_node		*tmp;
	t_sphere	sphere;
	t_sphere	sphere2;
	t_vec		center;
	t_vec		center2;

	// vector
	center = init_vector(0.0f, 0.0f, 0.0f);
	center2 = init_vector(1.0f, 1.0f, 1.0f);
	// sphere
	sphere.radius = 2.0f;
	sphere.center = center;
	sphere2.radius = 1.0f;
	sphere2.center = center2;
	// node
	node = init_node(SPHERE, &sphere);
	node2 = init_node(SPHERE, &sphere2);
	node_add(&node, node2);
	
	// TEST
	tmp = node;
	while (tmp != NULL)
	{
		t_sphere	*s;

		s = (t_sphere *)(tmp->data);
		printf("type: %d\n", tmp->type);
		if (tmp->type == SPHERE)
		{
			printf("Hey la sphere\n");
			printf("radius: %f\n", s->radius);
			printf("center: x: %f\t%f\t%f\n", s->center.x, s->center.y, s->center.z);
		}
		tmp = tmp->next;
	}
	return (0);
}
