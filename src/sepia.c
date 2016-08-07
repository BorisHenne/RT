/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 00:20:42 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/05 04:45:43 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

t_color		set_bw_color(t_color c)
{
	t_color	s;


	int		m = (c.r + c.g + c.b) / 3;

	s = init_color(m, m, m);
	check_color(&s);
	return (s);
}

t_color		set_sepia_color(t_color c)
{
	t_color	s;
	t_color	sepia;
//	int		m;

	sepia = init_color(94, 38, 18);
//
	s.r = (c.r * .393) + (c.g *.769) + (c.b * .189);
	s.g = (c.r * .349) + (c.g *.686) + (c.b * .168);
	s.b = (s.r * .272) + (s.g *.534) + (s.b * .131);

	s.r = (s.r + sepia.r) / 2;
	s.g = (s.g + sepia.g) / 2;
	s.b = (s.b + sepia.b) / 2;
	check_color(&s);
	return (s);

//

/*
	sepia = init_color(94, 38, 18);

	m = (c.r + c.g + c.b) / 3;
	if (m > 0 && m < 255)
	printf("m = %d\n", m);
	if (m == 0)
		m = 1;
	if (m > 71)
	{
		s.r = sepia.r - 71 % m;
		s.g = sepia.g - 71 % m;
		s.b = sepia.b - 71 % m;
	}
	else if (m < 71)
	{
		s.r = sepia.r + 71 % m;
		s.g = sepia.g + 71 % m;
		s.b = sepia.b + 71 % m;
	}
	else
	{
		return (sepia);
	}
	return (s);*/
}

void	*sepia_filter(void *mlx, void *img)
{
	void	*new;
	int		i;
	int		j;
	t_color	c;

	new = mlx_new_image(mlx, WIDTH, HEIGHT);
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			c = get_pixel_color(img, i, j);
			c = set_sepia_color(c);
			//c = set_bw_color(c);
			put_pixel_on_image(new, i, j, c);
			i++;
		}
		j++;
	}
	return (new);
}
