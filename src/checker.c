/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 06:11:33 by bhenne            #+#    #+#             */
/*   Updated: 2016/08/06 06:24:44 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <objects.h>
#include <stdio.h>

t_color	checkerboard(t_color color, t_vec coord_hit)
{
	int signe = 0;

	int p1;
	int p2;
	int p3;
	t_color color1;
	t_color color2;
	double L;

	L = 2;
	color1 = color;
	color2.r = 0.1;
	color2.g = 0.1;
	color2.b = 0.1;	
	int test = 0;

	p1 = coord_hit.x * L;
	p2 = coord_hit.y * L;
	p3 = coord_hit.z * L;

	signe += coord_hit.x < 0 ? 1 : 0;
	signe += coord_hit.y < 0 ? 1 : 0;
	signe += coord_hit.z < 0 ? 1 : 0;

	test += p1 % 2 == 0 ? 1 : 0;
	test += p2 % 2 == 0 ? 1 : 0;
	test += p3 % 2 == 0 ? 1 : 0;

	if (signe % 2 == 0)
		return(test % 2 == 0 ? color2 : color1);
	else
		return(test % 2 == 0 ? color1 : color2);
}
