/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 06:11:33 by bhenne            #+#    #+#             */
/*   Updated: 2016/08/06 01:59:16 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <objects.h>
#include <stdio.h>

t_color	checkerboard(t_color color, t_vec coord_hit)
{

	int p1;
	int p2;
	int p3;
	t_color color1;
	t_color color2;
	double L;

	L = 0.1;
	color1 = color;
	color2.r = 0.1;
	color2.g = 0.1;
	color2.b = 0.1;	
	int test = 0;

	p1 = (int)(coord_hit.x / L * PRECISION);
	p1 /= (double)PRECISION;
	p2 = (int)(coord_hit.y / L * PRECISION);
	p2 /= (double)PRECISION;
	p3 = (int)(coord_hit.z / L * PRECISION);
	p3 /= (double)PRECISION;
	
	test += coord_hit.x < 0 ? 1 : 0;
	test += coord_hit.z < 0 ? 1 : 0;
	test += coord_hit.y < 0 ? 1 : 0;
	if (p3 % 2 == 0)
	{
		if((((p1 % 2) == 0) && ((p2 % 2) == 0)) || (((p1 % 2) != 0) && ((p2 % 2) != 0)))
			return(test % 2 == 0 ? color2 : color1);
		else
			return(test % 2 == 0 ? color1 : color2);
	}
	else
	{
		if((((p1 % 2) == 0) && ((p2 % 2) == 0)) || (((p1 % 2) != 0) && ((p2 % 2) != 0)))
			return(test % 2 == 0 ? color1 : color2);
		else
			return(test % 2 == 0 ? color2 : color1);
	}
}


