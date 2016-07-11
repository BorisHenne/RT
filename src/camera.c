/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:20:20 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/12 00:49:39 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_vec		calc_vec_init(t_cam cam)
{
	t_vec	dir;
	t_vec	ver;
	t_vec	hor;
	
	dir = scalar_product(cam.dir, cam.d);
	ver = scalar_product(cam.ver, (cam.h / 2.0f));
	hor = scalar_product(cam.hor, (cam.w / 2.0f));
	return (vec_add(cam.pos, vec_sub(vec_add(dir, ver), hor)));
}

t_cam		init_camera(t_vec pos, t_vec look, t_vec ver)
{
	t_cam	cam;

	cam.pos = pos;
	cam.ver = ver;
	cam.d = 1.0f;
	cam.h = 0.35f;
	cam.w = 0.5f;
	cam.dir = normalize(vec_sub(look, pos));
	cam.hor = cross_product(ver, cam.dir);
	cam.ver = cross_product(cam.hor, cam.dir);
	cam.init = calc_vec_init(cam);
	return (cam);
}

t_vec		calc_vec_dir(int x, int y, t_cam cam)
{
	double	x_indent;
	double	y_indent;
	t_vec	hor;
	t_vec	ver;

	x_indent = cam.w / (double)WIDTH;
	y_indent = cam.h / (double)HEIGHT;
	hor = scalar_product(cam.hor, (x_indent * (double)x));
	ver = scalar_product(cam.ver, (y_indent * (double)y));
	return (vec_sub(vec_sub(vec_add(cam.init, hor), ver), cam.pos));
}
