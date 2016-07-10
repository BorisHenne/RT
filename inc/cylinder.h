/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:30:13 by tlepeche          #+#    #+#             */
/*   Updated: 2016/07/10 04:43:20 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CYLINDER_H
# define _CYLINDER_H

typedef struct	s_cylinder
{
	double		radius;
	t_vec		start_point;
	t_vec		dir;
	double		lenght;
	t_color		color;

}				t_cylinder;

#endif
