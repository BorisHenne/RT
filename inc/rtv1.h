/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:48:17 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/08 08:12:27 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RTV1_H
# define _RTV1_H
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# include <libft.h>
# define ESCAPE	53

# define WIDTH	640
# define HEIGHT 480

/*color*/

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

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

/*--------sphere*/

typedef struct		s_sphere
{
	double			radius;
	t_vec			center; 
	t_color			*color;
}					t_sphere;

/*------camera*/ 
typedef struct		s_cam
{
	t_vec			ori;
	t_vec			dir;
	t_vec			right;
	t_vec			down;
}					t_cam;
/*
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
   */
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

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	t_vec			pos_plan;
	t_cam			cam;
	int				fd;
}					t_env;










int	key_hook(int keycode, t_env *e);
t_vec				*init_vector(double x, double y, double z);
double				get_length(t_vec *vec);
void				normalize(t_vec *vec);

void				vec_add(t_vec *res, t_vec *a, t_vec *b);
void				vec_sub(t_vec *res, t_vec *a, t_vec *b);
void       			mul_vec(t_vec *res, t_vec *a, t_vec *b);
void				mul_vec_val(t_vec *res, t_vec *p, double val);
t_vec				*cross_product(t_vec *a, t_vec *b);
t_vec				*scalar_product(t_vec *vec, double n);
double				dot_product(t_vec *a, t_vec *b);
int					draw_scene(t_env *env);
t_vec				*normalize(t_vec *vec);

#endif
