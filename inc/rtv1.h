/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:48:17 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/08 01:28:40 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RTV1_H
# define _RTV1_H
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# define ESCAPE	53

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	int				fd;
}					t_env;

/*color*/

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

/*---Keyhook*/

int	key_hook(int keycode, t_env *e);

/*-----------------*/
/*--------- objects*/
/*-----------------*/

/*---vectors*/

typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

t_vec				*init_vector(double x, double y, double z);
double				get_length(t_vec *vec);
void				normalize(t_vec *vec);

t_vec				*vec_add(t_vec *a, t_vec *b);
t_vec				*vec_sub(t_vec *a, t_vec *b);
t_vec				*cross_product(t_vec *a, t_vec *b);
t_vec				*scalar_product(t_vec *vec, double n);
double				dot_product(t_vec *a, t_vec *b);

/*--------sphere*/

typedef struct		s_sphere
{
	double			radius;
	t_vec			center; 
	t_color			*color;
}					t_sphere;

/*------camera*/ 

typedef	struct 		s_cam
{
	double			viewplaneWidth;
	double			viewplaneHeight;
	double			viewplaneDist;
	double			xRes;
	double			yRes;

	t_vec			*camPos;
	t_vec			*vecDir;
	t_vec			*upVec;
	t_vec			*rightVec;
	t_vec			*viewplaneUpLeft;
}					t_cam;

/* target camera */

typedef	struct		s_targetCam
{
	t_vec			*lookAtPoint;
}					t_targetCam;

/*virtual plan*/



/*-------coord renvoyees*/

typedef struct		s_coord
{
/* distance */
	double			t;
	t_color			*color;
	int				bool;
}					t_coord;
#endif
