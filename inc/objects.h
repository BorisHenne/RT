/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:46:59 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/21 05:59:39 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OBJECTS_H
# define _OBJECTS_H
# include <vector.h>

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct s_hit
{
	int			id;
	double 		t;
	t_color		color;
	int			bool;
	t_vec		point_norm; // a calculer pour la brillance
	int			specular;
}				t_hit;

/*
 * Sphere
 */
/*typedef struct		s_sphere
{
	double			radius;
	t_vec			center; 
	t_color			color;
}					t_sphere;
*/
/*
 * Plane
 */
/*typedef struct		s_plane
{
	t_vec			pos;
	t_vec			normal;
	t_color			color;					
}					t_plane;
*/
#endif
