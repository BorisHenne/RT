/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:48:17 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/07 02:07:12 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RTV1_H
# define _RTV1_H
# include <math.h>
# include <stdlib.h>
# define ESCAPE	53

typedef struct		 s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*render;
	int				projection;
	int				rotation;
	int				color_depth;
	int				size_line;
	int				endian;
	char			*map_name;
	int				fd;
	int				rows;
	int				columns;
	float			span;
	float			x;
	float			y;
	int				pan_x;
	int				pan_y;
	int				depth;
	int				smooth;
	int				max;
	int				min;
	int				center_x;
	int				center_y;
	int				down;
	int				up;
	unsigned int	(*color)(struct s_env *);
}					t_env;


#endif
