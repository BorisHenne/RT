/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:44:00 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/16 03:47:48 by nbelouni         ###   ########.fr       */
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

t_vec		vec_rot_x(t_vec a, double angle);
t_vec		vec_rot_y(t_vec a, double angle);
t_vec		vec_rot_z(t_vec a, double angle);

double		dot_product(t_vec a, t_vec b);
double		get_length(t_vec vec);

#endif
