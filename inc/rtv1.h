/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:48:17 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/21 05:47:08 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RTV1_H
# define _RTV1_H

# include <math.h>
# include <stdlib.h>

# include <mlx.h>
# include <libft.h>

# include <camera.h>
# include <cone.h>
# include <cylinder.h>
# include <node.h>
# include <find_closest_object.h>
# include <light.h>
# include <plane.h>
# include <ray.h>
# include <scene.h>
# include <sphere.h>
# include <vector.h>

# define ESCAPE	53
# define WIDTH 1920
# define HEIGHT 1080
# define PRECISION 10000000

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	t_vec			pos_plan;
	t_cam			cam;
	int				fd;
}					t_env;

int					key_hook(int keycode, t_env *e);
int					draw_scene(t_env *env, t_scene scene);
double				deg_to_rad(double angle);
t_color				add_color(t_color a, t_color b);
void				check_color(t_color *color);
#endif
