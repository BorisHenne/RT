/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elipsoid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 03:53:08 by tlepeche          #+#    #+#             */
/*   Updated: 2016/08/14 00:26:07 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _elips_H
# define _elips_H

# include <ray.h>
# include <objects.h>
# include <quad.h>

typedef struct	s_elips
{
	double		radius;
	t_vec		center;
	t_quad		quad;
	t_color		color;
	int			specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;
}				t_elips;
/*
typedef struct	s_coord
{
	double	t;
	t_color	color;
	int	bool;
}		t_hit;
*/

double		find_elips_det(t_ray *ray, t_elips *elips, double *a, double *b);
void		find_elips_closest_hit(double a, double b, double det, t_hit *hit);
t_hit		is_elips_hit(t_ray *ray, t_elips *elips);

#endif
