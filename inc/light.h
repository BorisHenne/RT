/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 22:39:57 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/14 02:01:22 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LIGHT_H
# define	LIGHT_H

# include <scene.h>
# include <ray.h>

typedef struct		s_light
{
	t_vec		pos;
	t_color		color; // non utilise pour le moment
	// Add pleins de trucs trop ouf sa mere
}			t_light;

t_coord		apply_light(t_scene scene, t_coord curr_pixel, t_ray cam_ray);

#endif
