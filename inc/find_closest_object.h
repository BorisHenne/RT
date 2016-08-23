/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_object.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 03:06:03 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/18 16:27:09 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_CLOSEST_OBJECT
# define FIND_CLOSEST_OBJECT

t_hit		find_closest_object(t_node *nodes, t_ray *ray);
t_hit		init_hit(void);
t_hit		get_hit(t_ray *ray, t_node *tmp, int is_neg);

#endif
