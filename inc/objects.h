/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:46:59 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/25 16:10:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OBJECTS_H
# define _OBJECTS_H
# include <vector.h>

# define NONE		0
# define MARBLE		1

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct s_hit
{
	int			type;
	double 		t;
	double 		t_max;
	double		radius;
	t_color		color;
	int			bool;
	t_vec		point_norm; // a calculer pour la brillance
	int			specular;
	double		reflection;
	double		opacity;	//0 a 1
	double		ref_index; //indice de refraction
	int			is_negativ; //1 si negatif, 0 sinon
	int			texture;
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
