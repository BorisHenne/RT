/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:31:39 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/10 01:52:16 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct	s_scene
{
	t_cam		*cam;
	int			xRes;
	int			yRes;
	t_node		*nodes;
}				t_scene;

t_scene			*init_scene(t_cam *cam, int xRes, int yRes);

#endif
