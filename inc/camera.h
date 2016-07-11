/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:20:28 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/12 00:18:49 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CAMERA_H
# define _CAMERA_H

typedef struct		s_cam
{
	t_vec		pos;
	t_vec		dir;
	t_vec		hor;		// right
	t_vec		ver;		// up
	t_vec		init;		// upLeft
	double		w;		// HEIGHT
	double		h;		// WIDTH
	double		d;		// DIST
}			t_cam;

t_cam	init_camera(t_vec pos, t_vec look, t_vec ver);
t_vec	calc_vec_dir(int x, int y, t_cam cam);

#endif
