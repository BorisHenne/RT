/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 01:45:04 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/13 22:43:54 by nbelouni         ###   ########.fr       */
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
	t_color	mixed_color[(blur_lvl * 2 + 1) * (blur_lvl * 2 + 1)];
	t_color	new_color;
	void	*blurred_img;
	int		max;
//	int		blur;

	if (!(blurred_img = mlx_new_image(env->mlx, WIDTH, HEIGHT)))
		return (NULL);
	i = -1;
	while (++i < (blur_lvl * 2 + 1) * (blur_lvl * 2 + 1))
		mixed_color[i] = init_color(0, 0, 0);
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			max = (blur_lvl * 2 + 1) * (blur_lvl * 2 + 1);
			x = 0;
			while (x < blur_lvl * 2 + 1)
			{
				y = 0;
				while (y < blur_lvl * 2 + 1)
				{
					if (!((i - blur_lvl  + x < 0 || i - blur_lvl  + x > WIDTH)  && (j - blur_lvl + y < 0 || j - blur_lvl + y > HEIGHT)))
						mixed_color[x * blur_lvl + y] = get_pixel_color(env->img, i - blur_lvl + x, j - blur_lvl + y);
					y++;
				}
				x++;
			}

			x = 0;
			new_color = init_color(mixed_color[x].r, mixed_color[x].g, mixed_color[x].b);
			while (++x < max)
			{
			//	new_color = add_color(new_color, mixed_color[x]);
				if (mixed_color[x].r > 0 || mixed_color[x].g > 0 || mixed_color[x].b > 0)
				{
					new_color.r = new_color.r + mixed_color[x].r;
					new_color.g = new_color.g + mixed_color[x].g;
					new_color.b = new_color.b + mixed_color[x].b;
					if (new_color.r > 0)
					{
						printf("NC x : %d ___ r : %f, g : %f, b : %f\n", x, new_color.r, new_color.g, new_color.b);
					if (mixed_color[x].r == 0)
						printf("MX x : %d ___ r : %f, g : %f, b : %f\n", x, mixed_color[x].r, mixed_color[x].g, mixed_color[x].b);
					}
				}
			}
//			printf("x : %d\n", x);
//			if (new_color.r > 0)
//			{
//				printf("r : %f, g : %f, b : %f\n", new_color.r, new_color.g, new_color.b);
				new_color.r /= (blur_lvl * 2 + 1) * (blur_lvl * 2 + 1);
				new_color.g /= (blur_lvl * 2 + 1) * (blur_lvl * 2 + 1);
				new_color.b /= (blur_lvl * 2 + 1) * (blur_lvl * 2 + 1);
//				printf("r : %f, g : %f, b : %f\n", new_color.r, new_color.g, new_color.b);
				check_color(&new_color);
//			}
			put_pixel_on_image(blurred_img, i, j, new_color);
		}
	}
	return (blurred_img);
}
