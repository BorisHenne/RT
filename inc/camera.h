/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:41:59 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/09 23:50:31 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CAMERA_H
# define _CAMERA_H
# include "rtv1.h"
# include "vector.h"
# include "objects.h"

/*------camera*/ 
typedef struct		s_cam
{
	t_vec			*ori;
	t_vec			*dir;
	t_vec			*hor;
	t_vec			*vert;
	t_vec			*pos_init_plane;
}					t_cam;

/*-------coord renvoyees*/

typedef struct		s_coord
{
	/* distance */
	double			t;
	t_color			*color;
	int				bool;
}					t_coord;

void				init_cam(t_vec ori, t_vec look, t_vec init_vec, t_cam *cam);
t_coord				is_hit(t_cam *cam, t_sphere *sphere);
t_vec				*calcul_vect_dir(int x, int y, t_cam *cam);
#endif
