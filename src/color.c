/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 06:54:08 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/21 06:54:41 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		check_color(t_color *color)
{
	if (color->r < 0)
		color->r = 0;
	else if (color->r > 255)
		color->r = 255;

	if (color->g < 0)
		color->g = 0;
	else if (color->g > 255)
		color->g = 255;

	if (color->b < 0)
		color->b = 0;
	else if (color->b > 255)
		color->b = 255;
}

t_color		add_color(t_color a, t_color b)
{
	t_color res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	check_color(&res);
	return res;
}

t_color		init_color(int r, int g, int b)
{
	t_color res;

	res.r = r;
	res.g = g;
	res.b = b;
	check_color(&res);
	return (res);
}

t_color mult_color(t_color ref, double coef)
{
	t_color res;

	res.r = (ref.r * coef);
	res.g = (ref.g * coef);
	res.b = (ref.b * coef);
	check_color(&res);
	return (res);
}
