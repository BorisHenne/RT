/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:13:12 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/22 01:27:22 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SPHERE_H
# define _SPHERE_H

# include <ray.h>
# include <objects.h>

typedef struct	s_sphere
{
	double		radius;
	t_vec		center;
	t_color		color;
	int			specular;
	double		reflection;
	double		opacity;
	double		ref_index;
}				t_sphere;
/*
typedef struct	s_coord
{
	double	t;
	t_color	color;
	int	bool;
}		t_hit;
*/

double		find_sphere_det(t_ray ray, t_sphere sphere, double *a, double *b);
double		find_sphere_closest_hit(double a, double b, double det);
t_hit		is_sphere_hit(t_ray ray, t_sphere sphere);

#endif
