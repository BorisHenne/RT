/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:30:13 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/14 01:11:22 by nbelouni         ###   ########.fr       */
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
//	t_vec		rot;
	//t_vec		dir;
	double		length;
	t_color		color;

}				t_cylinder;

t_coord is_cylinder_hit(t_ray ray, t_cylinder cylinder);

#endif
