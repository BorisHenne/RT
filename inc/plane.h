/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 03:17:42 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/24 00:45:23 by tlepeche         ###   ########.fr       */
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
}					t_plane;

t_hit				is_plane_hit(t_ray ray, t_plane plan);

#endif
