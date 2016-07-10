/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:03:34 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/10 04:04:46 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double find_plane_closest_hit(t_cam *cam, t_plan *plan)
{
	if((dot_product(plan->normal, cam->dir)) == 0)
		return(0);
	else
		return(-(dot_product(plan->normal, cam->ori)) / (dot_product(plan->normal,
				cam->dir)));
}

t_coord	is_plane_hit(t_cam *cam, t_plan *plan)
{
	t_coord hit;
	
	hit.color = (t_color *)malloc(sizeof(t_color));
	hit.bool = 0;
	hit.t = 0;
	hit.color->r = 0;
	hit.color->g = 0;
	hit.color->b = 0;
	

	if(find_plane_closest_hit(cam, plan) != 0)
	{
		hit.bool = 1;
		hit.t = find_plane_closest_hit(cam, plan);
		hit.color = plan->color;
	}
	return (hit);
}
