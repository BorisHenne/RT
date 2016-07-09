/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:50:11 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/10 00:10:28 by sduprey          ###   ########.fr       */
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
	t_node	*node;
	t_cam	*cam;

	cam = inti_cam();
	node = init_node(CAMERA, cam);
	return (0);
}
