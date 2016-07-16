/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 00:35:14 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/16 08:01:07 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RAY_H
# define	RAY_H

#include <vector.h>

typedef struct	s_ray
{
	t_vec		pos;
	t_vec		dir;
	double		length;
}				t_ray;

#endif
