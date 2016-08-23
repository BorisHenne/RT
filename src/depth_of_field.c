/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_of_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:28:30 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/22 19:53:41 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

t_color		depth_of_field(t_env *env, int  blur_lvl, int i, int j, t_blur *blur_array)
{
	int		x;
	int		y;
	t_color	*mixed_color;
	t_color	new_color;
	int		max;
	int		n_color;
	int		n_black;
	double	ref_t;

	max = (blur_lvl * 2 + 1) * (blur_lvl * 2 + 1);
	if (!(mixed_color = (t_color *)malloc(sizeof(t_color) * max)))
		return (init_color(0, 0, 0));
	x = -1;
	while (++x < max)
		mixed_color[x] = init_color(0, 0, 0);
	ref_t = blur_array[i * HEIGHT + j].t;
	x = 0;
	n_color = 0;
	n_black = 0;
	while (x < blur_lvl * 2 + 1)
	{
		y = 0;
		while (y < blur_lvl * 2 + 1)
		{
			if ((((i - blur_lvl + x) * HEIGHT) + (j - blur_lvl + y)) >= 0 &&
			(((i  - blur_lvl + x) * HEIGHT) + (j - blur_lvl + y)) < HEIGHT * WIDTH  &&
			ref_t <= blur_array[((i - blur_lvl + x) * HEIGHT) + (j - blur_lvl + y)].t)
			{
				if (i - blur_lvl + x >= 0 ||
					i - blur_lvl + x < WIDTH ||
					j - blur_lvl + y >=  0 ||
					j - blur_lvl + y < HEIGHT)
				{
					mixed_color[n_color] = get_pixel_color(env->img, i - blur_lvl + x, j - blur_lvl + y);
					if (mixed_color[n_color].r == 0 && mixed_color[n_color].g == 0 && mixed_color[n_color].b == 0)
						n_black++;
					n_color++;
				}
			}
			y++;
		}
		x++;
	}

	if (n_color == n_black)
		return (mixed_color[0]);
	x = 0;
	new_color = mixed_color[x];
	while (++x < n_color)
	{
		new_color.r += mixed_color[x].r;
		new_color.g += mixed_color[x].g;
		new_color.b += mixed_color[x].b;
	}
	new_color.r /= n_color;
	new_color.g /= n_color;
	new_color.b /= n_color;
	check_color(&new_color);
	free(mixed_color);
	return (new_color);
}

void		*apply_depth_of_field(t_env *env, t_blur *array, double dof)
{
	void	*blurred_img;
	int		blur_lvl;
	t_color	new_color;
	int		i;
	int		j;

	if (!(blurred_img = mlx_new_image(env->mlx, WIDTH, HEIGHT)))
		return (NULL);
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			new_color = init_color(0, 0, 0);
			blur_lvl = (int)(fabs(dof - array[i * HEIGHT + j].t));
			if (blur_lvl > 15)
					blur_lvl = 15;
			if (blur_lvl > 0)
				new_color = depth_of_field(env, blur_lvl, i, j, array);
			else
				new_color = get_pixel_color(env->img, i, j);
			put_pixel_on_image(blurred_img, i, j, new_color);
		}
	}
	return (blurred_img);
}
