/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 00:07:56 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/14 05:36:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <aa.h>

// CHEAT
#include <stdio.h>

t_color		get_pixel_color(void *img, int x, int y)
{
	t_color	c;
	char	*data;
	int		i;
	int		bpp;
	int		sl;
	int		endian;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > WIDTH - 1)
		x = WIDTH - 1;
	if (y > HEIGHT - 1)
		y = HEIGHT - 1;

	data = mlx_get_data_addr(img, &bpp, &sl, &endian);
	bpp /= 8;
	i = x * bpp + y * sl;
	//
	c.b = data[i];
	c.g = data[i + 1];
	c.r = data[i + 2];
	if (c.r < 0)
		c.r = c.r + 256;
	if (c.g < 0)
		c.g = c.g + 256;
	if (c.b < 0)
		c.b = c.b + 256;
	return (c);
}

t_color		get_median_value(t_color *av, int max)
{
	int	i;
	int modif = 1;

	i = 0;
	while (modif)
	{
		modif = 0;
		i = 1;
		while (i < max)
		{
			int a = av[i - 1].r + av[i - 1].g + av[i - 1].b;
			int b = av[i].r + av[i].g + av[i].b;
			if (a > b)
			{
				modif = 1;
				t_color	tmp = av[i - 1];
				av[i - 1] = av[i];
				av[i] = tmp;
			}
			i++;
		}
	}
	return (av[4]);
}

t_color		get_av_color(void *img, int x, int y, int mode)
{
	t_color	*av;
	t_color	c;
	int		i;
	int		j;
	int		k;
	//

	av = (t_color *)malloc(sizeof(t_color) * 9);

	//
	//

	j = y - 1;
	k = 0;
	while (j <= y + 1)
	{
		i = x - 1;
		while (i <= x + 1)
		{
			av[k] = get_pixel_color(img, i, j);
			k++;
			i++;
		}
		j++;
	}
	//*
	if (mode == 1)
	{
		return (get_median_value(av, 9));
	}
	else
	{
		i = 0;
		c.r = 0;
		c.g = 0;
		c.b = 0;
		while (i < 9)
		{
			c.r += av[i].r;
			c.g += av[i].g;
			c.b += av[i].b;
			i++;
		}
		c.r /= 9;
		c.g /= 9;
		c.b /= 9;
		//printf("k = %d\n", k);
		return (c);
	}
}

void	*aa(void *mlx, void *img, int mode)
{
	void	*aa;
	int		i;
	int		j;
	t_color	c;
	//
	/*
	   int		imin = 560;
	   int		jmin = 700;
	   int		id = 5;
	   int		jd = 5;
	   */
	(void)aa;
	(void)mlx;

	printf("aa %d\n", mode);
	aa = mlx_new_image(mlx, WIDTH, HEIGHT);
	//
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			c = get_av_color(img, i, j, mode);
			put_pixel_on_image(aa, i, j, c);
			//if (i > imin && i < imin + id && j > jmin && j < jmin + jd)
			//	printf("aaa %d, %d: %d\t%d\t%d\n", i, j, (int)c.r, (int)c.g, (int)c.b);
			i++;
		}
		j++;
	}
	return (aa);
}
