/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:50:11 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/10 03:19:18 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

#define CAMERA 1

t_node		*init_node(int type, void *data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->type = type;
	node->data = data;
	return (node);
}

int			main(void)
{
	t_vec	*ori;
	t_vec	*look;
	t_vec	*init_vec;

	t_node	*node;
	t_cam	*cam;

	cam = (t_cam *)malloc(sizeof(t_cam));
	ori = init_vector(0.0f, 0.0f, 0.0f);
	look = init_vector(0.0f, 0.0f, 0.0f);
	init_vec = init_vector(0.0f, 0.0f, 0.0f);

	cam = init_cam(&ori, look, init_vec, cam);
	//node = init_node(CAMERA, cam);
	return (0);
}
