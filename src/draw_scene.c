/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/09 05:13:46 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
int         put_pixel_on_image(void *img, int x, int y, t_color *color)
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
	data[i] = color->b;
	data[i + 1] = color->g;
	data[i + 2] = color->r;
	return (0);
}

//#include <stdio.h>
int		draw_scene(t_env *env)
{
	int		x;
	int		y;

	t_vec ori;
	ori.x = 0.0;
	ori.y = 0.0;
	ori.z = 0.0;
	t_vec look;
	look.x = 0.0;
	look.y = 0.0;
	look.z = 1.0;
	t_vec init_vec;
	init_vec.x = 0.0;
	init_vec.y = 1.0;
	init_vec.z = 0.0;
	t_cam cam;
	
	init_cam(ori, look, init_vec, &cam);
	
	t_sphere	sphere;
	sphere.radius = 4.0;
	sphere.center.x = 0.0;
	sphere.center.y = 0.0;
	sphere.center.z = 10.0;
	if (!(sphere.color = (t_color *)malloc(sizeof(t_color))))
		return (-1);
	sphere.color->r = 123;
	sphere.color->g = 0;
	sphere.color->b = 0;

	t_coord		drawn_pixel;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			cam.dir = calcul_vect_dir(x, y, &cam);
//			printf("cam.dir : x = %f, y = %f, z = %f\n", cam.dir->x, cam.dir->y, cam.dir->z);
			drawn_pixel = is_hit(&cam, &sphere);
			put_pixel_on_image(env->img, x, y, drawn_pixel.color);
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
