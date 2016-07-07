/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:34:01 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/07 06:43:39 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	struct	s_vector
{
	double	x;
	double	y;
	double	z;
}		t_vector;

t_vector	*init_vector(double x, double y, double z);
double		get_length(t_vector *vec);
void		normalize(t_vector *vec);

t_vector	*vec_add(t_vector *a, t_vector *b);
t_vector	*vec_sub(t_vector *a, t_vector *b);
t_vector	*cross_product(t_vector *a, t_vector *b);
t_vector	*scalar_product(t_vector *vec, double n);
double		dot_product(t_vector *a, t_vector *b);

