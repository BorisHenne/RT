/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 03:17:42 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/14 00:19:10 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

typedef struct		s_plane
{
	t_vec			pos;
	t_vec			normal;
	t_color			color;					
	int				specular;
	double			reflection;
	double			opacity;
	double			ref_index;
	int				is_negativ;
	int				texture;
}					t_plane;

t_hit				is_plane_hit(t_ray *ray, t_plane *plan);
double				find_plane_hit(t_ray *ray, t_plane *plan);

#endif
