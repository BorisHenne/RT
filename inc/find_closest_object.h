/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_object.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 03:06:03 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/23 14:15:26 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_CLOSEST_OBJECT
# define FIND_CLOSEST_OBJECT

int			neg_exists(t_node *tmp);
t_hit		find_closest_object(t_node *nodes, t_ray *ray);
t_hit		init_hit(void);
t_hit		get_hit(t_ray *ray, t_node *tmp, int is_neg);

#endif
