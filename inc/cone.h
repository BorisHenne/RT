/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:25:00 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/20 03:15:14 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONE_H
# define _CONE_H

# include <rtv1.h>
# include <objects.h>

typedef struct	s_cone
{
	t_vec		pos;
	t_vec		dir;
	double		len;
	double		ang;
	double		r;
	t_color		color;
}				t_cone;

t_coord		is_cone_hit(t_ray ray, t_cone cone);

#endif
