/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:41:15 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/23 20:00:40 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_scene		*init_scene(void)
{
	t_scene	*s;
	t_blur	*tmp;
	int		i;

	i = -1;
	if (!(tmp = (t_blur *)malloc(sizeof(t_blur) * HEIGHT * WIDTH)))
		return (NULL);
	while (++i < HEIGHT * WIDTH)
	{
		tmp[i].t = 0;
		tmp[i].p_obj = 0;
	}
	if (!(s = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	s->w = WIDTH;
	s->h = HEIGHT;
	s->objects = NULL;
	s->lights = NULL;
	s->is_dof = 0;
	s->dof = 0;
	s->blur_array = tmp;
	s->is_real = 0;
	s->blur = 0;
	s->filter = NONE;
	s->ambient = 0.0;
	return (s);
}

void		add_camera(t_scene *s, t_cam cam)
{
	s->cam = cam;
}
