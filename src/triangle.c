/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 08:42:55 by bhenne            #+#    #+#             */
/*   Updated: 2016/08/22 15:53:15 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>
#include <objects.h>
#define eps 1e-8

t_hit is_trian_hit(t_ray *ray, t_triangle *triangle)
{
	t_hit hit;
	t_vec e1;
	t_vec e2;
	t_vec q , p;
	t_vec tvec;
	t_vec normal;
	double det, invdet, u, v;
	
	hit.bool = 0;
	hit.t = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	
	e1 = vec_sub(triangle->v0, triangle->v1);
	e2 = vec_sub(triangle->v0, triangle->v2);
	normal = cross_product(e1, e2);
	normal = normalize(normal);
	p = cross_product(ray->dir, e2);
	det = dot_product(e1, p);
	invdet = 1 / det;
	tvec = vec_sub(triangle->v0, ray->pos);
	u = dot_product(tvec, p) * invdet;
	q = cross_product(tvec, e1);
	v = dot_product(ray->dir, q) * invdet;
	if((dot_product(e2, q) * invdet) > (double)(1.0 / PRECISION))
	{
		hit.bool = 1;
		if(det > -(double)(1.0 /PRECISION) && det < (double)(1.0 / PRECISION))
			hit.bool = 0;
		if(u < 0 || u > 1)
			hit.bool = 0;
		if(v < 0 || u + v > 1)
			hit.bool = 0;

		hit.type = TRIAN;
		hit.t = (dot_product(e2, q) * invdet);
//		printf("%f\n", hit.t);
		hit.color = triangle->color;
		hit.point_norm.x = -normal.x;
		hit.point_norm.y = -normal.y;
		hit.point_norm.z = -normal.z;
		hit.reflection = triangle->reflection;
		hit.specular = triangle->specular;
		hit.opacity = triangle->opacity;
		hit.ref_index = triangle->ref_index;
		hit.is_negativ = triangle->is_negativ;
		hit.texture = triangle->texture;		
}
	return(hit);
}
