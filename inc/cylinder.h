/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:30:13 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/24 00:45:14 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CYLINDER_H
# define _CYLINDER_H

# include <ray.h>
# include <objects.h>
# include <math.h>

typedef struct	s_cylinder
{
	double		radius;
	t_vec		pos;
	t_vec		dir;
	double		length;
	double		r;
	double		h;
	t_color		color;
	int			specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
}				t_cylinder;

t_hit is_cylinder_hit(t_ray ray, t_cylinder cylinder);

#endif
