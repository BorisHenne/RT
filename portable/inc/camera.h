/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:33:46 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/07 06:43:34 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	struct	s_camera
{
	double		viewplaneWidth;
	double		viewplaneHeight;
	double		viewplaneDist;

	t_vector	*camPos;
	t_vector	*vecDir;
	t_vector	*upVec;
	t_vector	*rightVec;
	t_vector	*viewplaneUpLeft;
}				t_camera;
