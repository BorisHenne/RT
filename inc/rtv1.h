/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:48:17 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/07 05:24:23 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RTV1_H
# define _RTV1_H
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# define ESCAPE	53

typedef struct		 s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	int				fd;			
}					t_env;

int	key_hook(int keycode, t_env *e);

/*--------- objects*/
/*---vectors*/
typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

/*----sphere*/

typedef struct		s_sphere
{
	double			radius;
	t_vec			center; 
}					t_sphere;

/*-------coord renvoyees*/
typedef struct		s_coord
{
   /* distance */
	double			t;
	t_color			color;
	int				bool;
}					t_coord;

typedef struct		s_color
{
	int				R;
	int				G;
	int				B;
}					t_color;


#endif
