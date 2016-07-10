/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 02:18:07 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/10 02:00:29 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//addition de 2 vecteurs (a + b)
t_vec	*add_vec(t_vec *a, t_vec *b)
{
	t_vec	*res;

	if (!(res = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	if(!a || !b)
		return (NULL);
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	return (res);
}

// soustraction de 2 vecteurs (a - b)
t_vec	*sub_vec(t_vec *a, t_vec *b)
{
	t_vec	*res;

	if (!(res = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	if(!a || !b)
		return (NULL);
	res->x = b->x - a->x;
	res->y = b->y - a->y;
	res->z = b->z - a->z;
	return (res);
}

// multiplication de 2 vecteurs (a * b)
// = cross product = produit vectoriel
t_vec	*mul_vec(t_vec *a, t_vec *b)
{
	t_vec	*res;

	if (!(res = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	if (!a || !b)
		return (NULL);
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
	return (res);
}

// multiplication d'un vecteur par un reel (ex: 5 * a)
t_vec	*mul_vec_val(t_vec *p, double val)
{
	t_vec	*res;

	if (!(res = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	if (!p)
		return (NULL);
	res->x = p->x * val;
	res->y = p->y * val;
	res->z = p->z * val;
	return (res);
}

// produit scalaire d'un vecteur (angle entre les 2 vecteurs)
double		dot_product(t_vec *a, t_vec *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

//normalisation d'un vecteur (le mettre dans un repere connu)
t_vec	*normalize(t_vec *vec)
{
	double a;
	double b;
	double c;
	double norm;
	t_vec *vec_norm;

	if (!(vec_norm = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	a = pow(vec->x, 2);
	b = pow(vec->y, 2);
	c = pow(vec->z, 2);
	norm = sqrt(a + b + c);
	
	vec_norm->x = vec->x / norm;
	vec_norm->y = vec->y / norm;
	vec_norm->z = vec->z / norm;
	return (vec_norm);
}

/*
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
