/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:44:00 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/09 23:44:51 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VECTOR_H
# define _VECTOR_H
# include "rtv1.h"

/*---vectors*/

typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

t_vec				*init_vector(double x, double y, double z);
double				get_length(t_vec *vec);
t_vec				*add_vec(t_vec *a, t_vec *b);
t_vec				*sub_vec(t_vec *a, t_vec *b);
t_vec				*mul_vec(t_vec *a, t_vec *b);
t_vec				*mul_vec_val(t_vec *p, double val);
t_vec				*cross_product(t_vec *a, t_vec *b);
t_vec				*scalar_product(t_vec *vec, double n);
double				dot_product(t_vec *a, t_vec *b);
t_vec				*normalize(t_vec *vec);

#endif
