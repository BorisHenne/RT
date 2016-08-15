/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 01:45:04 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/15 03:07:06 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>

void		*apply_blur(t_env *env, int  blur_lvl)
{
	int		i;
	int		j;
	int		x;
	int		y;
	t_color	*mixed_color;
	t_color	new_color;
	void	*blurred_img;
	int		max;
	int		n_color;

	if (blur_lvl <= 0)
		return (env->img);
	if (!(blurred_img = mlx_new_image(env->mlx, WIDTH, HEIGHT)))
		return (NULL);
	max = (blur_lvl * 2 + 1) * (blur_lvl * 2 + 1);
	if (!(mixed_color = (t_color *)malloc(sizeof(t_color) * max)))
		return (NULL);
	i = -1;
	while (++i < max)
		mixed_color[i] = init_color(0, 0, 0);
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			x = 0;
			n_color = 0;
			while (x < blur_lvl * 2 + 1)
			{
				y = 0;
				while (y < blur_lvl * 2 + 1)
				{
					if (i - blur_lvl + x >= 0 ||
						i - blur_lvl + x < WIDTH ||
						j - blur_lvl + y >=  0 ||
					   	j - blur_lvl + y < HEIGHT)
					{
						mixed_color[n_color] = get_pixel_color(env->img, i - blur_lvl + x, j - blur_lvl + y);
						n_color++;
					}
					y++;
				}
				x++;
			}

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
			put_pixel_on_image(blurred_img, i, j, new_color);
		}
	}
	free(mixed_color);
	return (blurred_img);
}
