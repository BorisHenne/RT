/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:48:17 by bhenne            #+#    #+#             */
/*   Updated: 2016/08/12 23:18:34 by nbelouni         ###   ########.fr       */
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
# include <parse.h>
# include <plane.h>
# include <ray.h>
# include <refraction.h>
# include <scene.h>
# include <sphere.h>
# include <vector.h>
# include <elipsoid.h>
# include <quad.h>

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
t_color				mult_color(t_color ref, double coef);
t_color				init_color(int r, int g, int b);

int					is_black_edge(t_hit *hit);

t_color				sub_color(t_color a, t_color b);
void				write_vector(t_vec v, char *name);
double				apply_marble_noise(int x, int y, double res, double **tab_noise);
double				apply_wood_noise(int x, int y, double res, double **tab_noise);
t_color				checkerboard(t_color color, t_vec vec);
int					is_black_edge(t_hit *hit);

t_color				color_render(t_scene scene, t_ray start, double noise);
#endif
