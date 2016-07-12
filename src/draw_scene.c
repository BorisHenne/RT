/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/13 01:03:17 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
int         put_pixel_on_image(void *img, int x, int y, t_color color)
{
	char    *data;
	int     i;
	int     bpp;
	int     sl;
	int     endian;

	data = mlx_get_data_addr(img, &bpp, &sl, &endian);
	bpp /= 8;
	i = x * bpp + y * sl;
	if (x >= WIDTH || y >= HEIGHT)
		return (0);
	data[i] = color.b;
	data[i + 1] = color.g;
	data[i + 2] = color.r;
	return (0);
}

#include <stdio.h>
int		draw_scene(t_env *env)
{
	int		x;
	int		y;

	t_vec ori;
	ori.x = 0.0;
	ori.y = 0.0;
	ori.z = -8.0;
	t_vec look;
	//	look = rotation avec valeur a mettre en radian pour le moment;
	look.x = 0;
	look.y = 0.0;
	look.z = M_PI/2;
	t_vec init_vec;
	init_vec.x = 0.0;
	init_vec.y = 1.0;
	init_vec.z = 0.0;
	t_cam cam;

	cam = init_camera(ori, look, init_vec);

	t_sphere	sphere;
	sphere.radius = 0.4;
	sphere.center.x = 0.0;
	sphere.center.y = 0.0;
	sphere.center.z = 8.0;
	sphere.color.r = 123;
	sphere.color.g = 0;
	sphere.color.b = 0;


	t_cylinder	cylinder;
	cylinder.radius = 0.2;
	cylinder.pos.x = 0.0;
	cylinder.pos.y = -0.8;
	cylinder.pos.z = 5.0;
	cylinder.rot.x = 1.0;
	cylinder.rot.y = 1.0;
	cylinder.rot.z = 1.0;
	cylinder.length = 2.0;
	cylinder.color.r = 0;
	cylinder.color.g = 123;
	cylinder.color.b = 0;

	/*
	   t_plan		plan;
	   plan.pos.x = -2.0;
	   plan.pos.y = -1.0;
	   plan.pos.z = 0.0;	
	   plan.norma.x = 1.0;
	   plan.norma.y = 1.0;
	   plan.normal.z = 1.0;
	   if (!(plan.color = (t_color *)malloc(sizeof(t_color))))
	   return(-1);
	   plan.color->r = 0;
	   plan.color->g = 0;
	   plan.color->b = 123;

*/

	t_coord		drawn_pixel;
	t_coord		tmp;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			cam.dir = calc_vec_dir(x, y, cam);
			drawn_pixel = is_sphere_hit(cam, sphere);
			tmp = is_cylinder_hit(cam, cylinder);
			//			drawn_pixel = is_cylinder_hit(cam, cylinder);
			if (tmp.bool == 1)
			{
				if (drawn_pixel.bool == 0)
					drawn_pixel = tmp;
				else if (tmp.t < drawn_pixel.t)
					drawn_pixel = tmp;
			}
			if (drawn_pixel.bool == 1)
				put_pixel_on_image(env->img, x, y, drawn_pixel.color);
			else
				put_pixel_on_image(env->img, x, y, drawn_pixel.color);
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
