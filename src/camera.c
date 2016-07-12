/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:20:20 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/12 07:19:26 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

t_vec		calc_vec_init(t_cam cam)
{
	(void)cam;
	t_vec	dir;
	
	dir = scalar_product(cam.dir, cam.d);
	return(dir);
}

t_cam		init_camera(t_vec pos, t_vec look, t_vec ver)
{
	t_cam	cam;

	cam.pos = pos;
	cam.ver = ver;
	cam.d = 1.0f;
	cam.h = 0.35f;
	cam.w = 0.5f;
	cam.dir = vec_sub(look, pos);
	cam.dir = normalize(cam.dir);
	return (cam);
}

t_vec		calc_vec_dir(int x, int y, t_cam cam)
{
	double	x_indent;
	double	y_indent;
	t_vec	res;

	x_indent = cam.w / (double)WIDTH;
	y_indent = cam.h / (double)HEIGHT;

	res.x = ((x - (double)WIDTH/2.0) * x_indent);
	res.y = ((y - (double)HEIGHT/2.0) * y_indent);
	res.z = cam.d;

	// calcul pour faire une rotation sur l'axe des z;
	double a = 0;
	t_vec tmp;
	tmp.x = res.x * cos(a) - res.y * sin(a);
	tmp.y = res.x * sin(a) + res.y * cos(a);
	tmp.z = res.z;
//	printf("x = %.2f, y = %.2f, z = %.2f\n", res.x, res.y, res.z);

	return tmp;
}
