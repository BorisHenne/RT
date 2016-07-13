/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:03:34 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/13 05:28:28 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>
double find_plane_hit(t_cam *cam, t_plane *plan)
{
	double	tmp_magic;
	if((tmp_magic = dot_product(plan->normal, cam->dir)) == 0.0)
		return(0);
	else
		return((dot_product(plan->normal, vec_sub(cam->pos, plan->pos))) / tmp_magic);
}

t_coord	is_plane_hit(t_cam cam, t_plane plan)
{
	t_coord hit;
	double res;
	
	hit.bool = 0;
	hit.t = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	
	res = find_plane_hit(&cam, &plan);
	if (res != 0)
	{
		hit.bool = 1;
		hit.t = res;
		hit.color = plan.color;
	}
	return (hit);
}
