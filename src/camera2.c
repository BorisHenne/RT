/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:20:20 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/10 07:12:41 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h> // CHEAT

t_cam2		init_camera(t_vec pos, t_vec look, t_vec vert)
{
	t_cam2	cam;

	cam.pos = pos;
	cam.dir = normalize(vec_sub(look, pos));
	cam.hor = cross_product(vert, cam.dir);
	cam.vert = cross_product(cam.dir, cam.hor);
	cam.w = 0.5f;
	cam.h = 0.35f;
	cam.d = 1.0f;
	cam.init = calc_vec_init(&cam);
	return (cam);
}

/*
void		init_viewplane(t_cam cam)
{
}
*/

t_vec		calc_vec_init(t_cam *cam)
{
	t_vec	res;
	t_vec	dir;
	t_vec	vert;
	t_vec	hor;

	dir = scalar_product(cam->dir, cam->d);
	vert = scalar_product(cam->vert, (cam->height / 2.0f));
	hor = scalar_product(cam->hor, (cam->width / 2.0f));
	res = vec_add(vec_add(cam->pos, dir), vert);
	res = vec_sub(res , hor);
	return (res);
}

t_vec		calc_vec_dir(int x, int y, t_cam cam)
{
	double	x_indent;
	double	y_indent;
	t_vec	res;
	t_vec	tmp;

	x_indent = plane_width / (double)WIDTH;
	y_indent = plane_height / (double)HEIGHT;
	res = cross_product(cam.hor, (x_indent * (double)x));
	tmp = cross_product(cam.vert, (y_indent * (double)y));
	res = vec_add(res, cam.init);
	res = vec_sub(tmp, res);
	res = vec_sub(res, cam.pos);
	return (res);
}

int			main(void)
{
	t_cam2	cam;
	t_vec	pos;
	t_vec	look;
	t_vec	vert;

	pos = init_vector(0.0f, 0.0f, -3.0f);
	look = init_vector(0.0f, 0.0f, 10.0f);
	vert = init_vector(0.0f, 1.0f, 0.0f);
	// #################################################################
	printf("pos x: %f, y: %f, z: %f\n", pos.x, pos.y, pos.z);
	printf("look x: %f, y: %f, z: %f\n", look.x, look.y, look.z);
	printf("vert x: %f, y: %f, z: %f\n", vert.x, vert.y, vert.z);
	// #################################################################
	cam = init_camera(pos, look, vert);
	printf("cam.dir x: %f, y: %f, z: %f\n", cam.dir.x, cam.dir.y, cam.dir.z);
	return (0);
}
