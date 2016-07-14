/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 01:25:00 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/14 02:13:19 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONE_H
# define _CONE_H

# include <rtv1.h>

typedef struct	s_cone
{
	t_vec		pos;
	t_vec		dir;
	double		len;
	double		ang;
}				t_cone;

#endif
