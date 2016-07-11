/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:44:00 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/10 07:12:36 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VECTOR_H
# define _VECTOR_H

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
}		t_vec;

t_vec		init_vector(double x, double y, double z);
t_vec		vec_sub(t_vec a, t_vec b);
t_vec		vec_add(t_vec a, t_vec b);
t_vec		scalar_product(t_vec a, double b);
t_vec		cross_product(t_vec a, t_vec b);
t_vec		normalize(t_vec vec);
double		dot_product(t_vec a, t_vec b);

#endif
