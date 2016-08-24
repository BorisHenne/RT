/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 01:31:39 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/23 20:00:14 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# define REALISTIC		1
# define CARTOON		2

typedef struct	s_blur
{
	int			p_obj;
	double		t;
}				t_blur;

typedef struct	s_scene
{
	int			is_real;
	int			is_dof;
	int			dof;
	int			blur;
	int			filter;
	double		ambient;
	t_blur		*blur_array;
	t_cam		cam;
	int			w;
	int			h;
	t_node		*objects;
	t_node		*lights;
}				t_scene;

t_scene			*init_scene(void);
void			print_camera(t_cam *c);
void			write_scene(t_scene s);
void			add_camera(t_scene *s, t_cam cam);

#endif
