/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/06 07:03:41 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double		deg_to_rad(double angle)
{
	double res;

	res = angle * M_PI / 180;
	return res;
}

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

double	define_color(double color)
{
	if (color < 62)
		color = 0;
	if (color <= 124 && color > 62)
		color = 62;
	if (color <= 186 && color > 124)
		color = 124;
	else if (color > 186)
		color = 255;
	return (color);
}

//
//	Pour les contours noirs, checker dist entre 2 pt du meme object 
//	-> si 0 ou < 0.2 == noir
//
//	on se branle du plan pour l'instant
//

t_color	cartoon(t_color color)
{
	color.r = define_color(color.r);
	color.g = define_color(color.g);
	color.b = define_color(color.b);
	return (color);
}

int		is_black_edge(t_hit *hit)
{
	double	dist_min_max;
	double	edge_scale;

	if (hit->radius > 0.0)
		edge_scale = hit->radius / 2;
	else
		edge_scale = 0;

	dist_min_max = hit->t_max - hit->t;
	if (dist_min_max < edge_scale && dist_min_max > 0.0)
		return (1);
	return (0);
}

#include <stdio.h>


t_color color_render(t_scene scene, t_ray start, double noise)
{
	double	reflet;
	t_color final_color;
	t_color white;
	t_hit	drawn_pixel;
	int		r;

	r = 0;
	final_color = init_color(0, 0, 0);
	while (r < 3)
	{		
		drawn_pixel.reflection = (int)(PRECISION * drawn_pixel.reflection);
		drawn_pixel.reflection /= (double)PRECISION;
		if (r == 0 || drawn_pixel.reflection != 0)
		{
			reflet = pow(drawn_pixel.reflection, r * 3);
			drawn_pixel = find_closest_object(scene.objects, start);
			if (drawn_pixel.bool == 1)
			{
				if (scene.is_real == CARTOON && is_black_edge(&drawn_pixel))
					drawn_pixel.color = init_color(0, 0, 0);
				else
				{
					drawn_pixel.color = apply_light(scene, drawn_pixel, start);
					drawn_pixel.color = mult_color(drawn_pixel.color, reflet);
					drawn_pixel.color = add_color(drawn_pixel.color, apply_refraction(start, scene, drawn_pixel, reflet, noise));
					if (drawn_pixel.texture == MARBLE)
						drawn_pixel.color = mult_color(drawn_pixel.color, noise / 255);
					if (drawn_pixel.texture == CHECKER)
					{
						t_vec tmp = vec_add(start.pos, scalar_product(start.dir, drawn_pixel.t));
						drawn_pixel.color = checkerboard(drawn_pixel.color, tmp);
					}	
				}
			}
			else
				break;
			start.pos = vec_add(start.pos, scalar_product(start.dir, drawn_pixel.t)); 
			reflet = dot_product(start.dir, drawn_pixel.point_norm) * 2.0;
			start.dir = normalize(vec_sub(scalar_product(drawn_pixel.point_norm, reflet), start.dir));
			final_color = add_color(final_color, drawn_pixel.color);
		}
		if (scene.is_real == CARTOON)
		{
			//	printf("CARTOON\n");
			final_color = cartoon(final_color);
		}
		r++;
	}
	if (drawn_pixel.is_negativ == 1)
	{
		white = init_color(255, 255, 255);
		final_color = sub_color(white, final_color);
	}

	return (final_color);
}


int		draw_scene(t_env *env, t_scene scene)
{
	int		x;
	int		y;
	t_ray	start;
	t_color final_color;

	///////////////////////
	double	**tab_noise;

	y = 0;
	tab_noise = (double **)malloc(sizeof(double *) * HEIGHT);
	while (y < HEIGHT)
	{
		x = 0;
		tab_noise[y] = (double *)malloc(sizeof(double) * WIDTH);
		while (x < WIDTH)
		{
			tab_noise[y][x] = (rand() % 32768) / 32768.0;
			x++;
		}
		y++;
	}
	////////////////////////////

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			double noise;
			noise = apply_marble_noise(x, y, 50, tab_noise);
			start.pos = scene.cam.ray.pos;
			start.dir = normalize(calc_vec_dir(x, y, scene.cam, scene.cam.look_at));

			final_color = color_render(scene, start, noise);


			put_pixel_on_image(env->img, x, y, final_color);
		}

	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
