/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:03:34 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/21 06:58:51 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
# include <Stdio.h>

double find_plane_hit(t_ray ray, t_plane *plan)
{
	double	tmp_magic;
	if((tmp_magic = dot_product(plan->normal, ray.dir)) == 0.0)
		return(0);
	else
		return((dot_product(plan->normal, vec_sub(ray.pos, plan->pos))) / tmp_magic);
}

t_hit	is_plane_hit(t_ray ray, t_plane plan)
{
	t_hit hit;
	double res;

	hit.bool = 0;
	hit.t = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	
	res = find_plane_hit(ray, &plan);
	if (res != 0)
	{
		hit.t = (int)(res * PRECISION);
		hit.t /= (double)PRECISION;
		hit.bool = (hit.t == 0.0) ? 0 : 1;
		hit.color = plan.color;
		hit.point_norm.x = -plan.normal.x;
		hit.point_norm.y = -plan.normal.y;
		hit.point_norm.z = -plan.normal.z;
		hit.reflection = plan.reflection;
		hit.specular = plan.specular;
	}
	return (hit);
}
