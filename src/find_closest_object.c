/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 02:55:00 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/13 05:28:40 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>
t_coord		find_closest_object(t_node *nodes, t_cam cam)
{
	t_node		*tmp;
	t_coord		tmp_content;
	t_coord		closest_hit;

	closest_hit.t = 10;
	closest_hit.color.r = 0;
	closest_hit.color.g = 0;
	closest_hit.color.b = 0;
	closest_hit.bool = 0;
	tmp = nodes;
	while (tmp)
	{
		if (tmp->type == SPHERE)
			tmp_content = is_sphere_hit(cam, *(t_sphere *)tmp->data);
		else if (tmp->type == CYLINDER)
			tmp_content = is_cylinder_hit(cam, *(t_cylinder *)tmp->data);
		else if (tmp->type == PLANE)
			tmp_content = is_plane_hit(cam, *(t_plane *)tmp->data);
		if (tmp_content.bool == 1)
		{
			if ((closest_hit.bool == 0 || tmp_content.t <= closest_hit.t) && tmp_content.t > 0)
				closest_hit = tmp_content;
		}
		tmp = tmp->next;
	}
	return (closest_hit);
}
