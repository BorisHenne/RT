/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 04:59:45 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/04 04:26:24 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFRACTION_H
# define REFRACTION_H

//t_ray	find_refract_vect(t_ray start_ray, t_hit drawn_pixel, double c_r, double next_r, int is_in_object);
//t_color	apply_refraction(t_ray start, t_scene scene, t_hit drawn_pixe, double reflet);
t_color	apply_refraction(t_ray start, t_scene scene, t_hit drawn_pixe, double reflet, double noise);

#endif
