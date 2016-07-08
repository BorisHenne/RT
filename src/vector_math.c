/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 02:18:07 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/08 03:30:45 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		vec_add(t_vec *res, t_vec *a, t_vec *b)
{
	if(!res || !a || !b)
		return ;
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
}

void	vec_sub(t_vec *res, t_vec *a, t_vec *b)
{
	if(!res || !a || !b)
		return ;
	res->x = b->x - a->x;
	res->y = b->y - a->y;
	res->z = b->z - a->z;
}

void	mul_vec(t_vec *res, t_vec *a, t_vec *b)
{
	t_vec	tmp;

	if (!res || !a || !b)
		return ;
	tmp.x = a->x;
	tmp.y = a->y;
	tmp.z = a->z;
	res->x = tmp.y * b->z - tmp.z * b->y;
	res->y = tmp.z * b->x - tmp.x * b->z;
	res->z = tmp.x * b->y - tmp.y * b->x;
}

void	mul_vec_val(t_vec *res, t_vec *p, double val)
{
	if (!res || !p)
		return ;
	res->x = p->x * val;
	res->y = p->y * val;
	res->z = p->z * val;
}

double		dot_product(t_vec *a, t_vec *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

/*
   t_vector	cross_product(t_vector *a, t_vector *b)
   {
   double	x;
   double	y;
   double	z;

   x = (a->y * b->z) - (a->z * b->y);
   y = (a->z * b->x) - (a->x * b->z);
   z = (a->x * b->y) - (a->y * b->x);
   return (init_vector(x, y, z));
   }

   t_vector	*scalar_product(t_vector *vec, double n)
   {
   double	x;
   double	y;
   double	z;

   x = vec->x * n;
   y = vec->y * n;
   z = vec->z * n;
   return (init_vector(x, y, z));
   }

   double		dot_product(t_vector *a, t_vector *b)
   {
   double	dot;

   dot = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
// Verifier le cas du "dot <= 1" et remplacer par "dot < 1" si necessaire
if (dot > 0.0f && dot <= 1.0f)
return acos(dot);
return acos(0.0f);
}
*/
