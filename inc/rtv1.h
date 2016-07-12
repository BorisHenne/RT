/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:48:17 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/12 02:58:18 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RTV1_H
# define _RTV1_H

# include <math.h>
# include <stdlib.h>

# include <mlx.h>
# include <libft.h>

# include <camera.h>
# include <vector.h>
# include <node.h>
# include <scene.h>
# include <sphere.h>
# include <color.h>
# include <cylinder.h>

# define ESCAPE	53
# define WIDTH	640
# define HEIGHT 480

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
int					draw_scene(t_env *env);
#endif
