/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:41:15 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/10 01:52:08 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_scene		*init_scene(t_cam *cam, int w, int h)
{
	t_scene	*s;

	s = (t_scene *)malloc(sizeof(t_scene));
	s->xRes = w;
	s->yRes = h;
	s->nodes = NULL;	
	return (node);
}
