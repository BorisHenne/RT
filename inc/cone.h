/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:25:00 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/21 02:12:22 by nbelouni         ###   ########.fr       */
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
	int			reflection;
}				t_cone;

t_hit		is_cone_hit(t_ray ray, t_cone cone);

#endif
