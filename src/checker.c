/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 06:11:33 by bhenne            #+#    #+#             */
/*   Updated: 2016/08/23 19:03:42 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

t_color	checkerboard(t_color color, t_vec coord_hit)
{
	int		p1;
	int		p2;
	int		p3;
	double	L;
	int		test;

	L = 5;

	p1 = round(coord_hit.x * L);
	p2 = round(coord_hit.y * L);	
	p3 = round(coord_hit.z * L);

	test = 0;
	test += p1 % 2 == 0 ? 1 : 0;
	test += p2 % 2 == 0 ? 1 : 0;
	test += p3 % 2 == 0 ? 1 : 0;

	return (test % 2 == 0 ? mult_color(color, 0.1) : color);
}
