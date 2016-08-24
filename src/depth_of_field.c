/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_of_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:28:30 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/23 15:43:31 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

t_color		depth_of_field(t_env *env, int  blur_lvl, t_iter iter, t_blur *blur_array)
{
	t_iter	i;
	t_iter	curr;
	t_color	*mixed_color;
	int		n_color;
	int		n_black;
	double	ref_t;
	int		curr_index;

	if (!(mixed_color = new_color_array(blur_lvl)))
		return (init_color(0, 0, 0));
	ref_t = blur_array[iter.i * HEIGHT + iter.j].t;
	i.i = -1;
	n_color = 0;
	n_black = 0;
	while (++i.i < blur_lvl * 2 + 1)
	{
		i.j = -1;
		while (++i.j < blur_lvl * 2 + 1)
		{
			curr.i = iter.i - blur_lvl + i.i;
			curr.j = iter.j - blur_lvl + i.j;
			curr_index = curr.i * HEIGHT + curr.j;
			if (curr_index >= 0 && curr_index < HEIGHT * WIDTH &&
			ref_t <= blur_array[curr_index].t)
			{
				if (curr.i >= 0 || curr.i < WIDTH ||
					curr.j >= 0 || curr.j < HEIGHT)
				{
					mixed_color[n_color] = get_pixel_color(env->img, curr.i, curr.j);
					if (mixed_color[n_color].r == 0 && mixed_color[n_color].g == 0 && mixed_color[n_color].b == 0)
						n_black++;
					n_color++;
				}
			}
		}
	}
	if (n_color == n_black)
	{
		free(mixed_color);
		return (init_color(0, 0, 0));
	}
	return (mix_color(mixed_color, n_color));
}

void		*apply_depth_of_field(t_env *env, t_blur *array, double dof)
{
	void	*blurred_img;
	int		blur_lvl;
	t_color	new_color;
	t_iter	iter;

	if (!(blurred_img = mlx_new_image(env->mlx, WIDTH, HEIGHT)))
		return (NULL);
	iter.i = -1;
	while (++iter.i < WIDTH)
	{
		iter.j = -1;
		while (++iter.j < HEIGHT)
		{
			blur_lvl = ((int)(fabs(dof - array[iter.i * HEIGHT + iter.j].t))) * 2;
			if (blur_lvl > 10)
				blur_lvl = 10;
			if (blur_lvl > 0)
				new_color = depth_of_field(env, blur_lvl, iter, array);
			else
				new_color = get_pixel_color(env->img, iter.i, iter.j);
			put_pixel_on_image(blurred_img, iter.i, iter.j, new_color);
		}
	}
	return (blurred_img);
}
