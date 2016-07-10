/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 03:20:28 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/10 07:12:38 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CAMERA2_H
# define _CAMERA2_H

typedef struct	s_cam2
{
	t_vec		pos;
	t_vec		dir;
	t_vec		hor;	// right
	t_vec		vert;	// up
	t_vec		init;	// upLeft
	double		w;		// HEIGHT
	double		h;		// WIDTH
	double		d;		// DIST
}				t_cam2;

#endif
