/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:03:34 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/14 01:14:37 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double find_plane_hit(t_ray ray, t_plane *plan)
{
	double	tmp_magic;
	if((tmp_magic = dot_product(plan->normal, ray.dir)) == 0.0)
		return(0);
	else
		return((dot_product(plan->normal, vec_sub(ray.pos, plan->pos))) / tmp_magic);
}

t_coord	is_plane_hit(t_ray ray, t_plane plan)
{
	t_coord hit;
	double res;
	
	hit.bool = 0;
	hit.t = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	
	res = find_plane_hit(ray, &plan);
	if (res != 0)
	{
		hit.bool = 1;
		hit.t = res;
		hit.color = plan.color;
	}
	return (hit);
}
