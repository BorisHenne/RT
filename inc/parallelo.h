/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallelo.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 02:14:57 by bhenne            #+#    #+#             */
/*   Updated: 2016/08/22 17:06:10 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PARALLELO_H
# define _PARALLELO_H

# include <ray.h>
# include <objects.h>

typedef struct s_parallelo
{
	t_vec		v0;
	t_vec		v1;
	t_vec		v2;
	t_color		color;
	int			specular;
	double		reflection;
	double		opacity;
	double		ref_index;
	int			is_negativ;
	int			texture;
}				t_parallelo;

t_hit		is_parallelo_hit(t_ray *ray, t_parallelo *para);

#endif
