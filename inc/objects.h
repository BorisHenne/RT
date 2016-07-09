/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 23:46:59 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/10 00:04:14 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _OBJECTS_H
# define _OBJECTS_H
# include "rtv1.h"
# include "vector.h"
# include "camera.h"

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

/*--------sphere*/

typedef struct		s_sphere
{
	double			radius;
	t_vec			*center; 
	t_color			*color;
}					t_sphere;

#endif
