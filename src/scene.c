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

t_scene		*init_scene(int w, int h)
{
	t_scene	*s;

	s = (t_scene *)malloc(sizeof(t_scene));
	s->w = w;
	s->h = h;
	s->cam = NULL;
	s->nodes = NULL;	
	return (node);
}

void		add_camera(t_scene *s, t_cam *cam)
{
	s->cam = cam;
}

t_node		*add_node(t_node *node)
{

}
