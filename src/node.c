/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:50:11 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/14 01:39:15 by nbelouni         ###   ########.fr       */
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
