/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallelo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 16:27:06 by bhenne            #+#    #+#             */
/*   Updated: 2016/08/22 18:04:54 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>
#include <objects.h>

t_hit is_parallelo_hit(t_ray *ray, t_parallelo *para)
{
	t_hit hit;
	t_vec e1;
	t_vec e2;
	t_vec q, p;
	t_vec tvec;
	t_vec normal;
	double det, invdet, u , v;

	hit.bool = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;

	e1 = vec_sub(para->v0, para->v1);
	e2 = vec_sub(para->v0, para->v2);
	normal = cross_product(e1, e2);
	normal = normalize(normal);
	p = cross_product(ray->dir, e2);
	det = dot_product(e1, p);
	invdet = 1 / det;
	tvec = vec_sub(para->v0, ray->pos);
	u = dot_product(tvec, p) * invdet;
	q = cross_product(tvec, e1);
	v = dot_product(ray->dir , q) * invdet;
	if ((dot_product(e2, q) * invdet) > (double)(1 / PRECISION))
	{
		hit.bool = 1;
		if(det > -(double)(1 / PRECISION) && det < (double)(1 / PRECISION))
			hit.bool = 0;
		if(u < (double)(1 / PRECISION) || u > 1)
			hit.bool = 0;
		if(v < (double)(1 / PRECISION) || v > 1)
			hit.bool = 0;

		hit.type = PARA;
		hit.t = (dot_product(e2, q) * invdet);
		hit.color = para->color;
		hit.point_norm.x = -normal.x;
		hit.point_norm.y = -normal.y;
		hit.point_norm.z = -normal.z;
		hit.reflection = para->reflection;
		hit.specular = para->specular;
		hit.opacity = para->opacity;
		hit.ref_index = para->ref_index;
		hit.is_negativ = para->is_negativ;
		hit.texture = para->texture;
	}
	return(hit);	
}
