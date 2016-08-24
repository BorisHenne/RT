/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 01:45:04 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/23 13:36:00 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_color		mix_color(t_color *mixed_color, int n_color)
{
	t_color	new_color;
	int		x;

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

t_color		*new_color_array(int blur_lvl)
{
	int		x;
	int		max;
	t_color	*mixed_color;

	max = (blur_lvl * 2 + 1) * (blur_lvl * 2 + 1);
	if (!(mixed_color = (t_color *)malloc(sizeof(t_color) * max)))
		return (NULL);
	x = -1;
	while (++x < max)
		mixed_color[x] = init_color(0, 0, 0);
	return (mixed_color);
}

t_color		get_mixed_color(t_env *env, int blur, int i, int j)
{
	int		x;
	int		y;
	int		n;
	t_color	*tmp;

	if (!(tmp = new_color_array(blur)))
		return (init_color(0, 0, 0));
	x = -1;
	n = 0;
	while (++x < blur * 2 + 1)
	{
		y = -1;
		while (++y < blur * 2 + 1)
		{
			if (i - blur + x >= 0 || i - blur + x < WIDTH ||
			j - blur + y >= 0 || j - blur + y < HEIGHT)
			{
				tmp[n] = get_pixel_color(env->img, i - blur + x, j - blur + y);
				n++;
			}
		}
	}
	return (mix_color(tmp, n));
}

void		*apply_blur(t_env *env, int blur_lvl)
{
	int		i;
	int		j;
	t_color	new_color;
	void	*blurred_img;

	if (blur_lvl <= 0)
		return (env->img);
	if (!(blurred_img = mlx_new_image(env->mlx, WIDTH, HEIGHT)))
		return (NULL);
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			new_color = get_mixed_color(env, blur_lvl, i, j);
			put_pixel_on_image(blurred_img, i, j, new_color);
		}
	}
	return (blurred_img);
}
